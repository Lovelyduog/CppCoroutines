#!/usr/bin/env bash
# 跑单元测试：tools/test.sh [debug|release|asan]
# asan 预设带 AddressSanitizer/UBSan，协程寿命问题靠它抓
set -euo pipefail
cd "$(dirname "$0")/.."

preset="${1:-debug}"
cmake --preset "$preset"
cmake --build --preset "$preset" -j
ctest --preset "$preset"
