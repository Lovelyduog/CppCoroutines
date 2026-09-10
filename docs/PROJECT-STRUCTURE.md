# 工程结构方案

2026-09-10 与 agent 讨论定稿。目标：规范化仓库结构，为自研协程库铺路。

## 决策

1. **学习代码与库代码彻底分离**：学习代码全部进 `study/`，库代码走 `include/` + `src/`，互不掺杂，库长大后可独立演进。
2. **他人实践单独归档**：`01~09` 等搬运的实践进 `study/external/`，保持原样、不参与根构建（每个目录自带 CMakeLists，可单独构建）。
3. **thirdparty 暂不设计**：只留空目录，引入机制等真有需求时再定（候选：FetchContent 为主 + 本目录作缓存/vendor）。依赖 boost 的学习程序在第三方就绪前排除出构建。
4. **构建入口**：CMakePresets.json（debug/release）为主，`tools/` 放薄脚本（build/run/format）做补充。
5. **每个学习 .cpp 一个可执行文件**，沿用原仓库习惯，便于单独运行验证。

## 迁移映射

| 原位置 | 新位置 |
|---|---|
| `lesson-*.cpp/.s/.txt` | `study/lesson/` |
| `test-*.cpp/.hpp` | `study/test/` |
| `io.h`、`coroutine-demo.h` | `study/common/` |
| `01~09.*`、`co_await_and_co_yield.cpp` | `study/external/` |
| 原 `README.md`（学习笔记） | `docs/NOTES.md` |
| `a.out`（二进制产物） | 删除 |

## 结构

见仓库根 [README.md](../README.md) 的目录结构一节。

## 后续待定

- 协程库的名称与命名空间（`include/` 下层目录名）
- 库测试框架与目录（GTest/Catch2，经 thirdparty 引入）
- thirdparty 引入机制细化（ADR 待定）
