#include <iostream>
#include <coroutine>

template <typename T>
struct CoroutineTask {
    struct promise_type {
        T value;
        auto get_return_object() { return CoroutineTask{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_never initial_suspend() { return std::suspend_never{}; }
        std::suspend_never final_suspend() noexcept { return std::suspend_never{}; }
        void unhandled_exception() {}
        void return_value(T val) { value = val; }
    };

    std::coroutine_handle<promise_type> coroutine;

    CoroutineTask(std::coroutine_handle<promise_type> coro) : coroutine(coro) {}

    ~CoroutineTask() {
        if (coroutine)
            coroutine.destroy();
    }

    T get_result() { return coroutine.promise().value; }
};

template
operator co_await(){

}

template <typename T>
struct CoroutineTask2 {
    struct promise_type {
        T value;
        auto get_return_object() { return CoroutineTask2{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        auto initial_suspend() { return std::suspend_never{}; }
        auto final_suspend() noexcept { return std::suspend_never{}; }
        void unhandled_exception() {}
        void return_value(T val) { value = val; }
    };

    std::coroutine_handle<promise_type> coroutine;

    CoroutineTask2(std::coroutine_handle<promise_type> coro) : coroutine(coro) {}

    ~CoroutineTask2() {
        if (coroutine)
            coroutine.destroy();
    }

    T get_result() { return coroutine.promise().value; }
};

CoroutineTask<int> second_coroutine() {
    std::cout << "second_coroutine" << std::endl;
    co_return 1;
}

template <typename T>
CoroutineTask2<T> first_coroutine() {
    co_await second_coroutine();
    // std::cout << a << std::endl;
    co_return 'b';
}

int main() {
    CoroutineTask2<char> result = first_coroutine<char>();
    std::cout << result.get_result() << std::endl;

    return 0;
}