# CppCoroutines

个人 C++20 协程学习项目，目标是逐步演进出自研协程库。

- 学习笔记与结论见 [docs/NOTES.md](docs/NOTES.md)
- 工程结构方案见 [docs/PROJECT-STRUCTURE.md](docs/PROJECT-STRUCTURE.md)

## 目录结构

```
├── include/       # 协程库公开头文件（骨架）
├── src/           # 协程库实现（骨架）
├── study/         # 学习代码
│   ├── lesson/    #   基础学习程序（lesson-*）
│   ├── test/      #   实验与演进记录（test-*），每个 .cpp 一个可执行文件
│   ├── common/    #   学习代码共享的头文件
│   └── external/  #   他人学习实践的搬运（01~09），独立小项目，不参与根构建
├── thirdparty/    # 第三方库（暂空，FetchContent 缓存/vendor）
├── tools/         # build.sh / run.sh / format.sh
├── docs/          # 笔记、方案、ADR
└── build/         # 构建产物（gitignore）
```

## 构建

要求：CMake ≥ 3.20、g++ ≥ 11、C++20。

```bash
# 一键构建（默认 debug）
tools/build.sh

# 或直接使用 CMake 预设
cmake --preset debug
cmake --build --preset debug -j

# 构建并运行某个学习程序
tools/run.sh test-coroutine-order-7
```

依赖 boost 的学习程序（`test-boost-*.cpp`、`test-coroutine-order.cpp`）在第三方库引入前暂不编译，构建时会打印 skip 提示。
