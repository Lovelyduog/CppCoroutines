//
// Created by benny on 2022/1/31.
//
#define __cpp_lib_coroutine
#include <coroutine>
#include <exception>
#include <iostream>
#include <thread>

struct Generator {

  class ExhaustedException : std::exception {};
  // 首先构造promise_type
  struct promise_type {
    int value;
    bool is_ready = false;

    // 挂起时返回一个等待体，等待体规定了协程执行的逻辑
    std::suspend_always initial_suspend() { return {}; };

    // 销毁promise_type后调用 final_suspend,这两个函数主要作用是返回等待体
    std::suspend_always final_suspend() noexcept { return {}; }

    // yield_value调用在initial_suspend 之前
    std::suspend_always yield_value(int value) {
      this->value = value;
      is_ready = true;
      return {};
    }

    void unhandled_exception() {

    }

    // 函数返回Generator， 使用std::coroutine_handle<promise_type>::from_promise从promise_type对象上获取handle初始化Generator
    Generator get_return_object() {
      return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    void return_void() {}
  };

  std::coroutine_handle<promise_type> handle;

  bool has_next() {
    // https://en.cppreference.com/w/cpp/coroutine/coroutine_handle/done
    if (handle.done()) {
      return false;
    }

    if (!handle.promise().is_ready) {
      handle.resume();
    }

    if (handle.done()) {
      return false;
    } else {
      return true;
    }
  }

  int next() {
    if (has_next()) {
      handle.promise().is_ready = false;
      return handle.promise().value;
    }
    throw ExhaustedException();
  }

  explicit Generator(std::coroutine_handle<promise_type> handle) noexcept
      : handle(handle) {}

  Generator(Generator &&generator) noexcept
      : handle(std::exchange(generator.handle, {})) {}

  Generator(Generator &) = delete;
  Generator &operator=(Generator &) = delete;

  ~Generator() {
    if (handle) handle.destroy();
  }
};

Generator sequence() {
  int i = 0;
  while (i < 5) {
    co_yield i++;
  }
}

Generator fibonacci() {
  co_yield 0;
  co_yield 1;

  int a = 0;
  int b = 1;
  while (true) {
    co_yield a + b;
    b = a + b;
    a = b - a;
  }
}

class Fibonacci {
 public:
  int next() {
    if (a == -1) {
      a = 0;
      b = 1;
      return 0;
    }

    int next = b;
    b = a + b;
    a = b - a;
    return next;
  }

 private:
  int a = -1;
  int b = 0;
};

int main() {
  auto generator = fibonacci();
  auto fib = Fibonacci();
  for (int i = 0; i < 10; ++i) {
    if (generator.has_next()) {
      std::cout << generator.next() << " " << fib.next() << std::endl;
    } else {
      break;
    }
  }
  return 0;
}