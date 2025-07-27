# syntax=docker/dockerfile:1

# ベースイメージ
FROM ubuntu:22.04 AS base
WORKDIR /src
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
RUN pipx install norminette==3.3.55
ENV PATH="/root/.local/bin:$PATH"
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
    && rm -rf /var/lib/apt/lists/*
COPY --from=build /tmp/miniRT /tmp
ARG IN_DOCKER=yes
RUN --mount=type=bind,target=. \
    make test \
    && rm /tmp/miniRT

# 開発用コンテナイメージをビルドするステージ
FROM base as dev
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get DEBIAN_FRONTEND=noninteractive install -y --no-install-recommends \
    clang-format \
    clang-tidy \
    pipx \
    build-essential \
    libxext-dev \
    libbsd-dev \
    xorg \
    && rm -rf /var/lib/apt/lists/*
RUN pipx install norminette=3.3.55
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /miniRT
COPY . /miniRT

# 実行を行うステージ
FROM ubuntu:22.04 AS final
ARG UID=10001
RUN adduser \
    --disabled-password \
    --gecos "" \
    --home "/nonexistent" \
    --shell "/sbin/nologin" \
    --no-create-home \
    --uid "${UID}" \
    user
USER user
COPY --from=build /tmp/miniRT /bin
ENTRYPOINT ["/bin/miniRT"]
CMD []
