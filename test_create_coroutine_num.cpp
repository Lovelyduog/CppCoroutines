#define __cpp_lib_coroutine

#include <iostream>
#include <coroutine>
#include <future>
#include <chrono>

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


class CoroutineTask;

struct Awaiter3 {
  int value;

  // return false 表示该协程创建出来后挂起
  bool await_ready() {
    // 返回值设置为true 我们发现Coroutine（）没有挂起没有sleep，直接顺序执行了
    std::cout << "await_ready3" << std::endl; 
    return false;
  }

  // 在这个时候传出其他句柄，立刻resume该句柄
  // std::coroutine_handle<> await_suspend(std::coroutine_handle<> coroutine_handle) {
  //   std::cout << "await_suspend3" << std::endl;
  //   // std::async([=](){
  //   //   std::this_thread::sleep_for(5s);
  //   //   coroutine_handle.resume();
  //   // });
  //   return coroutine_handle;
  // }

  void await_suspend(std::coroutine_handle<> coroutine_handle) {
    std::cout << "await_suspend3" << std::endl;
    // std::async([=](){
    //   std::this_thread::sleep_for(5s);
    //   coroutine_handle.resume();
    // });
    return ;
  }

  int await_resume() {
    std::cout << "await_resume3" << std::endl;
    return value;
  }
  
};

#include <vector>
std::coroutine_handle<> g_coroutine_handle;


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
    g_coroutine_handle = coroutine_handle;
  }

  // 恢复后，会调用该函数将value 作为co_await单目运算符的返回值
  int await_resume() {
    std::cout << "await_resume" << std::endl;
    return value;
  }
};




struct CoroutineTask {
  struct promise_type {
    suspend_never initial_suspend() {
      std::cout << "initial_suspend2" << std::endl;
      return {};
    }

    Awaiter3 await_transform(CoroutineTask && task) {
      return {.value = 3 };
    }

    suspend_always final_suspend() noexcept {
      std::cout << "final_suspend2" << std::endl;
      return {};
    }

    CoroutineTask get_return_object() {
      std::cout << "get_return_object2" << std::endl;

      return {};
    }

    void return_void() {

    }


    void unhandled_exception() {

    }
  };
  
};



CoroutineTask Coroutine();
// test init_suspend  called num
CoroutineTask Coroutine(int i) {
  i++;
  if(i == 2){
    co_return;
  }
  co_await Coroutine(i);

  co_return;
};





int main(){
	// auto a = Coroutine(0);
	return 0;
}