#define __cpp_lib_coroutine

#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

void Fun() {
  std::cout << 1 << std::endl;
  std::cout << 2 << std::endl;
  std::cout << 3 << std::endl;
  std::cout << 4 << std::endl;
}

struct Result {
  struct promise_type {
    std::suspend_never initial_suspend() {
      return {};
    }

    std::suspend_never final_suspend() noexcept {
      return {};
    }

    Result get_return_object() {
      return {};
    }

    void return_void() {

    }

//    void return_value(int value) {
//
//    }

    void unhandled_exception() {

    }
  };
};

struct Awaiter {
  int value;

  // return false 表示该协程创建出来后挂起
  bool await_ready() {
    // 返回值设置为true 我们发现Coroutine（）没有挂起没有sleep，直接顺序执行了
    return false;
  }

  // 协程体挂起后，将当前挂起点句柄传给一个线程，由该线程唤醒
  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::async([=](){
      std::this_thread::sleep_for(2s);
      coroutine_handle.resume();
    });
  }

  // 恢复后，会调用该函数将value 作为co_await单目运算符的返回值
  int await_resume() {
    return value;
  }
};

// 只有在协程中才可以co_await 所以需要定义result携程
Result Coroutine() {
  std::cout << 1 << std::endl;
  // co_await可以操作的对象是await体
  std::cout << co_await Awaiter{.value = 1000} << std::endl;
  std::cout << 2 << std::endl;
  std::cout << 3 << std::endl;
  // co_await Awaiter 实际上是co_await await_ready的返回值的
  co_await std::suspend_always{};
  std::cout << 4 << std::endl;

  co_return;
};

//Result Coroutine(int start_value) {
//  std::cout << start_value << std::endl;
//  co_await std::suspend_always{};
//  std::cout << start_value + 1 << std::endl;
//
//  co_return 100;
//};

int main() {
  Coroutine();
  return 0;
}
