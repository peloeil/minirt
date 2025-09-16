# syntax=docker/dockerfile:1

# ベースイメージ
FROM ubuntu:22.04 AS base
WORKDIR /minirt-src
ENV DEBIAN_FRONTEND=noninteractive
RUN sed -i 's@archive.ubuntu.com@ftp.jaist.ac.jp/pub/Linux@g' /etc/apt/sources.list
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    make
ARG HOST_CWD
ENV HOST_CWD=$HOST_CWD

# コンパイルを行うステージのベース
FROM base AS build-base
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    git

# コンパイルを行うステージ
FROM build-base AS build
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make all && make clean

# compile_commands.json を生成するステージ
FROM build-base AS compile-commands
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    bear \
    pipx \
    moreutils
ARG PIPX_HOME=/opt/pipx
ARG PIPX_BIN_DIR=/usr/local/bin
RUN pipx install compdb
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make /tmp/miniRT/compile_commands.json

# 静的解析を行うステージ
FROM archlinux:base-devel AS check-base
WORKDIR /minirt-src
RUN --mount=type=cache,target=/var/cache/pacman,sharing=locked \
    pacman -Syu --noconfirm --needed \
    clang \
    python-pipx \
    libx11
ARG PIPX_HOME=/opt/pipx
ARG PIPX_BIN_DIR=/usr/local/bin
RUN pipx install norminette==3.3.55
ARG HOST_CWD
ENV HOST_CWD=$HOST_CWD
COPY --from=compile-commands /tmp/miniRT/mlx_linux/mlx.h /tmp/miniRT/mlx_linux/
COPY --from=compile-commands /tmp/miniRT/mlx_linux/mlx_int.h /tmp/miniRT/mlx_linux/
COPY --from=compile-commands /tmp/miniRT/compile_commands.json /tmp/miniRT/
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make check

# compile_commands.json を取り出すためのステージ
FROM scratch AS check
COPY --from=check-base /tmp/miniRT/compile_commands.json /

# 単体テスト、統合テストを行うステージ
FROM base AS test
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    git
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make test \
    && rm -rf /tmp/miniRT

# 開発用コンテナイメージをビルドするステージ
FROM base AS dev
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    clang-tidy \
    pipx \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    git \
    bear \
    moreutils
ARG PIPX_HOME=/opt/pipx
ARG PIPX_BIN_DIR=/usr/local/bin
RUN pipx install norminette==3.3.55
RUN pipx install c-formatter-42
RUN pipx install compdb

# 実行を行うステージ
FROM ubuntu:22.04 AS final
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    libxext6 \
    libbsd0
COPY --from=build /tmp/miniRT/miniRT /bin
ENTRYPOINT ["/bin/miniRT"]
CMD []
