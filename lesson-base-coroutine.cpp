#define __cpp_lib_coroutine

#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>
// #include <coroutine_handle>

using namespace std::chrono_literals;



struct Result {
  struct promise_type {
    promise_type(){
    }

    ~promise_type(){
    }
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

//    }

    void unhandled_exception() {

    }

    // 测试内存占用大小
    // int a[1000] ={};
    // int b = 0;
  };
};

void func(std::coroutine_handle<> coroutine_handle)
{
  coroutine_handle.resume();
  // coroutine_handle.destroy();
}

struct Awaiter {
  int value;
  bool await_ready() {
    return false;
  }


  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    // std::async(std::launch::async,[=](){
    //   std::this_thread::sleep_for(2s);
    //   coroutine_handle.resume();
    // });
    // coroutine_handle.resume();
    func(coroutine_handle);
  }

  int await_resume() {
    return value;
  }
};

Result Coroutine() {
  int b = 22;
  (void)b;
  co_await Awaiter{.value = 1000};
  // co_await std::suspend_always{};
  int a  = 22;
  (void)a;
  co_return;
};

Result test() {
  int b = 11;
  (void)11;
  co_await Awaiter{.value = 1000};
  // co_await std::suspend_always{};
  int a  = 33;
  (void)a;
  co_return;
};

int main() {
  Coroutine();
  test();
  getchar();
  return 0;
}
