#!/usr/bin/env bash
# 一键构建：tools/build.sh [debug|release]
set -euo pipefail
cd "$(dirname "$0")/.."

preset="${1:-debug}"
cmake --preset "$preset"
cmake --build --preset "$preset" -j
