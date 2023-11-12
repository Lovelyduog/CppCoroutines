#define __cpp_lib_coroutine

#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>
// #include <coroutine_handle>

using namespace std::chrono_literals;

void Fun() {
  std::cout << 1 << std::endl;
  std::cout << 2 << std::endl;
  std::cout << 3 << std::endl;
  std::cout << 4 << std::endl;
}

 struct suspend_always
  {
     bool await_ready() const noexcept { 
      try
      {
        std::cout << "suspend_always::await_ready" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      return false; 
    }

     void await_suspend(std::coroutine_handle<> handle) const noexcept {
      try
      {
        std::cout << "suspend_always::await_suspend" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
    }

     void await_resume() const noexcept {
      try
      {
        std::cout << "suspend_always::await_resume" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  };

 struct suspend_never
  {
     bool await_ready() const noexcept { 
      try
      {
        std::cout << "suspend_never::await_ready" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      return true; 
    }

     void await_suspend(std::coroutine_handle<> handle) const noexcept {
      try
      {
        std::cout << "suspend_never::await_suspend" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
    }

     void await_resume() const noexcept {
      try
      {
        std::cout << "suspend_never::await_resume" << std::endl;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
    }
  };


struct Result {
  struct promise_type {
    suspend_never initial_suspend() {
      std::cout << "initial_suspend" << std::endl;
      return {};
    }

    // suspend_never final_suspend() noexcept {
    //   std::cout << "final_suspend" << std::endl;
    //   return {};
    // }
    // 返回always当前协程结束后会挂起，需要再调用resume，c++协程提供了而挂起时挂起，以及获取值后挂起的两种可能性
    suspend_always final_suspend() noexcept {
      std::cout << "final_suspend" << std::endl;
      return {};
    }

    Result get_return_object() {
      std::cout << "get_return_object" << std::endl;

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

struct Result2 {
  struct promise_type {
    suspend_never initial_suspend() {
      std::cout << "initial_suspend2" << std::endl;
      return {};
    }

    // suspend_never final_suspend() noexcept {
    //   std::cout << "final_suspend" << std::endl;
    //   return {};
    // }
    // 返回always当前协程结束后会挂起，需要再调用resume，c++协程提供了而挂起时挂起，以及获取值后挂起的两种可能性
    suspend_always final_suspend() noexcept {
      std::cout << "final_suspend2" << std::endl;
      return {};
    }

    Result2 get_return_object() {
      std::cout << "get_return_object2" << std::endl;

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
    std::cout << "await_ready" << std::endl;
    return false;
  }

  // 协程体挂起后，将当前挂起点句柄传给一个线程，由该线程唤醒
  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::cout << "await_suspend" << std::endl;
    std::async([=](){
      std::this_thread::sleep_for(2s);
      coroutine_handle.resume();
    });
  }

  // 恢复后，会调用该函数将value 作为co_await单目运算符的返回值
  int await_resume() {
    std::cout << "await_resume" << std::endl;
    return value;
  }
};

struct Awaiter2 {
  int value;

  // return false 表示该协程创建出来后挂起
  bool await_ready() {
    // 返回值设置为true 我们发现Coroutine（）没有挂起没有sleep，直接顺序执行了
    std::cout << "await_ready2" << std::endl; 
    return false;
  }

  // 协程体挂起后，将当前挂起点句柄传给一个线程，由该线程唤醒
  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::cout << "await_suspend2" << std::endl;
    std::async([=](){
      std::this_thread::sleep_for(5s);
      coroutine_handle.resume();
    });
  }

  // 恢复后，会调用该函数将value 作为co_await单目运算符的返回值
  int await_resume() {
    std::cout << "await_resume2" << std::endl;
    return value;
  }
};

struct Awaiter3 {
  int value;

  // return false 表示该协程创建出来后挂起
  bool await_ready() {
    // 返回值设置为true 我们发现Coroutine（）没有挂起没有sleep，直接顺序执行了
    std::cout << "await_ready3" << std::endl; 
    return false;
  }

  // 并没有挂起，那这个作为返回值怎么传出有什么用呢？
  std::coroutine_handle<> await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::cout << "await_suspend3" << std::endl;
    // std::async([=](){
    //   std::this_thread::sleep_for(5s);
    //   coroutine_handle.resume();
    // });
    return coroutine_handle;
  }

  // bool await_suspend(std::coroutine_handle<> coroutine_handle) {

  //   return true;
  // }
  // bool await_suspend(std::coroutine_handle<> coroutine_handle) {

  //   return false;
  // }

  // void await_suspend(std::coroutine_handle<> coroutine_handle) {

  //   return ;
  // }

  // void await_suspend(std::coroutine_handle<> coroutine_handle) {
  //   std::cout << "await_suspend3" << std::endl;
  //   // std::async([=](){
  //   //   std::this_thread::sleep_for(5s);
  //   //   coroutine_handle.resume();
  //   // });
  //   return ;
  // }

  int await_resume() {
    std::cout << "await_resume3" << std::endl;
    return value;
  }
};


// 只有在协程中才可以co_await 所以需要定义result携程
Result Coroutine() {
  std::cout << 1 << std::endl;
  // co_await可以操作的对象是await体
  // 这里可以理解为initial_suspend返回的awaiter
  std::cout << co_await Awaiter{.value = 1000} << std::endl;
  std::cout << 2 << std::endl;
  std::cout << 3 << std::endl;
  std::cout << co_await Awaiter2{.value = 100} << std::endl;
  // co_await Awaiter 实际上是co_await await_ready的返回值的
  // 对比suspend_always和suspend_never效果
  // co_await std::suspend_always{};
  // co_await std::suspend_never{};
  std::cout << 4 << std::endl;
  auto a = co_await Awaiter3{.value = 100};
  // a.resume();
  std::cout << 5 << std::endl;

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
