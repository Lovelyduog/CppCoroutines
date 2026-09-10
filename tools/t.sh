#!/usr/bin/env bash
# 单元测试快捷入口：记不住 ctest/Catch2 命令时，看这里就够了。
#
#   tools/t.sh                          跑全部用例
#   tools/t.sh file test_task           只跑某个测试文件（名字可部分匹配，ctest 正则）
#   tools/t.sh case "值传播"             按用例名或标签跑，自动跨所有测试文件找（名字给子串即可）
#   tools/t.sh case "[smoke]"           标签筛选同理（写用例时记得加标签）
#   tools/t.sh case "值传播" test_task   用例名/标签 + 限定某个文件
#   tools/t.sh list                     列出全部用例
#   tools/t.sh list test_task           只列出某文件的用例
#
# 任何子命令前可加 -p <preset> 换构建预设（debug/release/asan，默认 debug）：
#   tools/t.sh -p asan case "[lifetime]"
#
# case 子命令末尾可用 "--" 透传参数给 Catch2，例如首败即停进调试器：
#   tools/t.sh case "[smoke]" -- --break
set -euo pipefail
cd "$(dirname "$0")/.."

usage() { grep '^#' "$0" | grep -v '^#!' | sed 's/^# \{0,1\}//' | sed '$d'; }

preset="debug"
if [[ "${1:-}" == "-p" ]]; then
    [[ $# -ge 2 ]] || { echo "usage: tools/t.sh -p <preset> <子命令>" >&2; exit 1; }
    preset="$2"; shift 2
fi

cmd="${1:-all}"
test_dir="build/$preset/tests"

build_quietly() {
    cmake --preset "$preset" >/dev/null
    cmake --build --preset "$preset" -j >/dev/null
}

run_one() {
    local bin="$1" filter="$2"; shift 2
    echo "-- $(basename "$bin")"
    "$bin" "$filter" "$@"
}

# 遍历测试可执行文件，只对「确有匹配用例」的执行 run_one
each_matching_binary() {
    local filter="$1" only_file="$2"; shift 2
    local bin name matched
    for bin in "$test_dir"/test_*; do
        [[ -x "$bin" ]] || continue
        name="$(basename "$bin")"
        if [[ -n "$only_file" && "$name" != "$only_file" && "$name" != "$only_file.out" ]]; then
            continue
        fi
        matched=$("$bin" --list-tests --verbosity quiet "$filter" 2>/dev/null | grep -c . || true)
        [[ "${matched:-0}" -gt 0 ]] || continue
        run_one "$bin" "$filter" "$@"
    done
}

case "$cmd" in
all)
    build_quietly
    exec ctest --preset "$preset"
    ;;
file)
    [[ $# -ge 2 ]] || { echo "usage: tools/t.sh file <文件名正则>" >&2; exit 1; }
    build_quietly
    exec ctest --preset "$preset" -R "$2"
    ;;
case)
    [[ $# -ge 2 ]] || { echo "usage: tools/t.sh case <用例名或标签> [文件名] [-- catch2参数...]" >&2; exit 1; }
    filter="$2"; only_file=""; extra=()
    # 名字给子串即可：无通配符且非标签时，自动包 *...* 按子串匹配
    if [[ "$filter" != *'*'* && "$filter" != '['* && "$filter" != '~'* ]]; then
        filter="*${filter}*"
    fi
    if [[ $# -ge 3 && "$3" != "--" ]]; then only_file="$3"; fi
    while [[ $# -gt 0 ]]; do
        if [[ "$1" == "--" ]]; then shift; extra=("$@"); break; fi
        shift
    done
    build_quietly
    echo "filter: $filter   preset: $preset"
    each_matching_binary "$filter" "$only_file" "${extra[@]}"
    ;;
list)
    build_quietly
    for bin in "$test_dir"/test_*; do
        [[ -x "$bin" ]] || continue
        name="$(basename "$bin")"
        if [[ -n "${2:-}" && "$name" != "${2:-}" && "$name" != "${2:-}.out" ]]; then continue; fi
        echo "== $name =="
        "$bin" --list-tests --verbosity quiet
    done
    ;;
help|-h|--help)
    usage
    ;;
*)
    usage
    echo "未知子命令: $cmd" >&2; exit 1
    ;;
esac
