#!/usr/bin/env bash
# 格式化库代码与学习代码：tools/format.sh
set -euo pipefail
cd "$(dirname "$0")/.."

if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format 未安装（sudo apt install clang-format）" >&2
    exit 1
fi

find include src study -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \
    | xargs -r clang-format -i -style=file:"$(dirname "$0")/../.clang-format"
echo "formatted."
