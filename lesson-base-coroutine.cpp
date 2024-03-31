#define __cpp_lib_coroutine

#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>
// #include <coroutine_handle>

using namespace std::chrono_literals;


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

//    }

    void unhandled_exception() {

    }
  };
};


struct Awaiter {
  int value;
  bool await_ready() {
    std::cout << "await_ready" << std::endl;
    return false;
  }

  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::cout << "await_suspend" << std::endl;
    std::async([=](){
      std::this_thread::sleep_for(2s);
      coroutine_handle.resume();
    });
  }

  int await_resume() {
    std::cout << "await_resume" << std::endl;
    return value;
  }
};

Result Coroutine() {
  std::cout << 1 << std::endl;
  std::cout << co_await Awaiter{.value = 1000} << std::endl;
  std::cout << 2 << std::endl;
//   co_await suspend_always{}; 
//   std::cout << 3 << std::endl;
  co_return;
};


int main() {
  Coroutine();
  getchar();
  return 0;
}
