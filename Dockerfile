# syntax=docker/dockerfile:1

# ベースイメージ
FROM ubuntu:22.04 AS base
WORKDIR /src
RUN sed -i 's@archive.ubuntu.com@ftp.jaist.ac.jp/pub/Linux@g' /etc/apt/sources.list
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    make \
    && rm -rf /var/lib/apt/lists/*

# 静的解析などを行うステージ
FROM base AS check
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    clang-format \
    clang-tidy \
    pipx \
    && rm -rf /var/lib/apt/lists/*
ARG PIPX_HOME=/opt/pipx
ARG PIPX_BIN_DIR=/usr/local/bin
RUN pipx install norminette==3.3.55
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make check

# コンパイルを行うステージ
FROM base AS build
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    git \
    && rm -rf /var/lib/apt/lists/*
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make all && make clean

# 単体テスト、統合テストを行うステージ
FROM base AS test
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    && rm -rf /var/lib/apt/lists/*
COPY --from=build /tmp/miniRT /tmp
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make test \
    && rm /tmp/miniRT

# 開発用コンテナイメージをビルドするステージ
FROM base AS dev
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    clang-format \
    clang-tidy \
    pipx \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    git \
    && rm -rf /var/lib/apt/lists/*
ARG PIPX_HOME=/opt/pipx
ARG PIPX_BIN_DIR=/usr/local/bin
RUN pipx install norminette==3.3.55

# 実行を行うステージ
FROM ubuntu:22.04 AS final
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    libxext6 \
    libbsd0 \
    && rm -rf /var/lib/apt/lists/*
COPY --from=build /tmp/miniRT /bin
ENTRYPOINT ["/bin/miniRT"]
CMD []
