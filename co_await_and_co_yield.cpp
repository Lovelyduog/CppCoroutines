
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

    std::suspend_always yield_value(int value) {
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
      : handle(generator.handle) {}

  Generator(Generator &) = delete;
  Generator &operator=(Generator &) = delete;

  ~Generator() {
    if (handle) handle.destroy();
  }
};

Generator fibonacci() {

  int a = 0;
  while (true) {
    co_await a++;
  }
}


Generator fibonacci2() {

  int a = 0;
  while (true) {
    co_yield a++;

  }
}

// 汇报上看两者毫无区别
/*co_yield expr等同于co_await promise.yield_value(expr)
当promise_type定义了await_transform 后，两者从功能上来说一样，co_yield算是对co_await的封装
*/ 



