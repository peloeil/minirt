# syntax=docker/dockerfile:1

# ベースイメージ
FROM ubuntu:22.04 AS base
WORKDIR /src
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends make

# 静的解析などを行うステージ
FROM base AS check
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    clang-format \
    clang-tidy \
    pipx \
    && rm -rf /var/lib/apt/lists/* \
    && pipx install norminette==3.3.55
RUN --mount=type=bind,target=. \
    make check

# 単体テスト、統合テストを行うステージ
FROM base AS test
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    && rm -rf /var/lib/apt/lists/*
RUN --mount=type=bind,target=. \
    make test && make fclean

# コンパイルを行うステージ
#    xorg \
FROM base AS build
RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libxext-dev \
    libbsd-dev \
    && rm -rf /var/lib/apt/lists/*
RUN --mount=type=bind,target=. \
    make all && make clean

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
