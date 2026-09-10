#include <iostream>
#include <coroutine>

// 定义一个简单的协程
struct MyCoroutine {
    struct promise_type {
        MyCoroutine get_return_object() {
            return MyCoroutine{};
        }
        std::suspend_never initial_suspend() {
            return {};
        }
        std::suspend_never final_suspend() noexcept {
            return {};
        }
        void return_void() {}
        void unhandled_exception() {
            std::cerr << "Unhandled exception in coroutine!" << std::endl;
        }
    };

    // 在协程中抛出异常的函数
    void throwError() {
        throw std::runtime_error("An exception occurred in the coroutine!");
    }
};

// 使用协程的函数
MyCoroutine myCoroutine() {
    try {
        co_await std::suspend_never{};
        std::cout << "Coroutine started." << std::endl;
        co_await std::suspend_never{};
        MyCoroutine{}.throwError();  // 在协程中调用可能抛出异常的函数
        co_await std::suspend_never{};
        std::cout << "Coroutine finished." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception in coroutine: " << e.what() << std::endl;
    }
}

int main() {
    auto coroutine = myCoroutine();
    coroutine.throwError();  // 主线程中调用可能抛出异常的函数
    getchar();
    return 0;
}