#!/usr/bin/env bash
# 构建并运行某个学习程序：tools/run.sh <目标名> [debug|release]
# 例：tools/run.sh test-coroutine-order-7
set -euo pipefail
cd "$(dirname "$0")/.."

if [ $# -lt 1 ]; then
    echo "usage: tools/run.sh <target> [debug|release]" >&2
    exit 1
fi

target="$1"
preset="${2:-debug}"
cmake --build --preset "$preset" --target "$target" -j
exec "build/${preset}/${target}"
