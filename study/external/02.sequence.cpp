//
// Created by benny on 2022/1/31.
//
#define __cpp_lib_coroutine
#include <coroutine>
#include <exception>
#include <iostream>
#include <thread>

struct Generator {

  class ExhaustedException: std::exception { };

  struct promise_type {
    int value = 999;
    bool is_ready = false;

    std::suspend_always initial_suspend() { return {}; };

    std::suspend_always final_suspend() noexcept { return {}; }

    std::suspend_always await_transform(int value) {
      this->value = value;
      is_ready = true;
      return {};
    }

    void unhandled_exception() {

    }

    Generator get_return_object() {
      return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
    }

    void return_void() { }
  };

  std::coroutine_handle<promise_type> handle;


  bool has_next() {
    // std::cout << "has_next" << std::endl;
    // https://en.cppreference.com/w/cpp/coroutine/coroutine_handle/done
    // 协程是否被挂起在最后一个挂起点

    // pass协程初始值

    return !handle.done();
  }

  int next() {
    if (has_next()) {
      // // promise_type 初值也会被记录在handle中
      // std::cout << handle.promise().is_ready << std::endl;
      // std::cout << handle.promise().value << std::endl;
      if (!handle.promise().is_ready) //调用co_await时，会将该值赋值为true
      {
        handle.resume();
      }

      auto  value = handle.promise().value;
      handle.resume();
      return value;
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
    co_await i++;
  }
}

Generator returns_generator() {
  auto g = sequence();
  if (g.has_next()) {
    std::cout << g.next() << std::endl;
  }
  return g;
}

// 怎么感觉co_await也可以直接当co_yield使用呢？
Generator fibonacci() {
  co_await 0;
  co_await 1;

  int a = 0;
  int b = 1;
  while (true) {
    int c = a + b ;
    co_await c;
    b = a + b;
    a = b - a;
  }
}


int main() {
  // auto generator = returns_generator();
  auto generator = fibonacci();
  for (int i = 0; i < 15; ++i) {
    if (generator.has_next()) {
      std::cout << generator.next() << std::endl;
    } else {
      break;
    }
  }

  return 0;
}


