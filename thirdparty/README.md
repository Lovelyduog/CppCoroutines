# thirdparty

第三方库存放目录，暂为空。

计划采用 FetchContent 作为主要引入机制，本目录将作为 FetchContent 的源码缓存；必须手工修改 vendor 的库才直接提交源码到这里。boost 依赖（`study/test/test-boost-*.cpp`、`test-coroutine-order.cpp`）等第三方就绪后再恢复编译。
