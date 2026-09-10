#include <catch2/catch_test_macros.hpp>
#include <coroutine>
#include <cstdio>

// 冒烟测试：验证 Catch2 链路 + C++20 协程工具链可用。
// 协程库第一个模块落地后，本文件可删除或改写为真实用例。

namespace {

bool g_executed = false;

struct smoke_task {
    struct promise_type {
        smoke_task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

smoke_task run_once() {
    g_executed = true;
    co_return;
}

} // namespace

TEST_CASE("C++20 协程可同步跑完并置位", "[smoke]") {
    g_executed = false;
    run_once();
    REQUIRE(g_executed);
}
