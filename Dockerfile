# syntax=docker/dockerfile:1

# ベースイメージ
FROM --platform=linux/amd64 debian:bookwarm AS base

RUN --mount=type=cache,target=/var/lib/apt,sharing=locked \
    --mount=type=cache,target=/var/cache/apt,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# formatter, norm のチェックを行うステージ
FROM base AS check

# コンパイルを行うステージ
FROM base AS build

# 実行を行うステージ
FROM --platform=linux/amd64 ubuntu:22.04 AS final

RUN adduser \
    --disabled-password \
    --gecos "" \
    --home "/user" \
    --shell "/sbin/nologin" \
    --no-create-home \
    --uid "${UID}" \
    user
USER user
WORKDIR /user
COPY --from=build /minirt/miniRT /user/miniRT
ENTRYPOINT ["/user/miniRT"]
CMD []
