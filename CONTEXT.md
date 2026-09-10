# CONTEXT

本仓库的术语表。仅收录已和项目所有者确认含义的词。

## 学习代码（study）

- **lesson**：跟随基础概念的学习程序（`study/lesson/`），每个 `.cpp` 一个可执行文件。
- **test（学习实验）**：项目所有者自己的实验与演进记录（`study/test/`），编号体现演进顺序（如 `test-coroutine-order-5-1` → `-7`）；不是自动化测试，不与未来库的单元测试混谈。
- **common**：学习代码共享的头文件（`study/common/`）。
- **external（外部实践）**：他人学习实践的搬运（`study/external/`，`01~09`），保持原样、不参与根构建。

## 协程库

- **cppcoroutines（库骨架）**：`include/` + `src/` 承载的自研协程库，目前仅 INTERFACE 目标；正式名称与命名空间待定，定名前不对外发布。

## 其他

- **单元测试**：`tests/` 下针对协程库的自动化测试（Catch2 v3 + ctest），必须确定性——事件循环可步进、时间可注入、不起真线程；与「test（学习实验）」严格区分。
- **asan 预设**：带 AddressSanitizer/UBSan 的测试构建（`tools/test.sh asan`），用于抓协程 handle 悬垂/泄漏类问题。
- **NOTES**：项目所有者的学习笔记与结论（`docs/NOTES.md`），持续追加。
