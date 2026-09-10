
#include <coroutine>
#include <future>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>

struct async_task_base
{
    virtual void completed() = 0;
    virtual void resume() = 0;
};


std::mutex m;
std::vector<std::shared_ptr<async_task_base>> g_resume_queue; //原来的 eventloop队列
std::vector<std::shared_ptr<async_task_base>> g_work_queue; //执行耗时操作线程队列


template <typename T>
struct AsyncAwaiter;


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
    promise_type(){
      std::cout << "promise_type" << std::endl;
    }

    ~promise_type(){
      std::cout << "~promise_type" << std::endl;
    }
    suspend_never initial_suspend() {
      std::cout << "initial_suspend" << std::endl;
      return {};
    }

    suspend_never final_suspend() noexcept {
      std::cout << "final_suspend" << std::endl;
      return {};
    }

    Result get_return_object() {
      std::cout << "get_return_object" << std::endl;

      return {};
    }
    void return_void() {
        std::cout << "return_void" << std::endl;
    }

//    void return_value(int value) {

//    }

    void unhandled_exception() {

    }
  };
};


template <typename ReturnType>
struct  AsyncThread
{
    using return_type = ReturnType;

    AsyncThread(std::function<return_type ()>&& func): func_(func){

    }
    std::function<return_type ()> func_;
};


template <typename ReturnType>
struct async_task: public async_task_base{
    async_task(AsyncAwaiter<ReturnType> &awaiter)
    :owner_(awaiter)
    {

    }

    void completed() override{
        std::cout << "async_task ::  completed ############" << std::endl;
        ReturnType result = owner_.func_();
        owner_.value_ = result;
    }

    void resume() override{
        std::cout << "async_task ::  resume ############" << std::endl;
        owner_.h_.resume();
    }
    AsyncAwaiter<ReturnType> &owner_ ;
};


template <typename ReturnType>
struct AsyncAwaiter
{
    using return_type = ReturnType;

    AsyncAwaiter(AsyncThread<ReturnType>& info){
        // std::cout<< " AsyncAwaiter(AsyncThread<ReturnType>& info)" << std::endl;
        value_ = return_type{};
        func_ = info.func_;
    }


    // 该awaite直接挂起
    bool await_ready() const noexcept { 
        return false; 
    }
    
    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        std::lock_guard<std::mutex> g(m);
        g_work_queue.emplace_back(std::shared_ptr<async_task_base>( new async_task<uint64_t>(*this)));
    }

    return_type await_resume() const noexcept { 
        // std::cout<< "AsyncAwaiter::await_resume" << std::endl;
        return value_;
    }

  
    std::function<return_type ()> func_;
    std::coroutine_handle<> h_; 
    return_type value_ = return_type();
};


template<typename T>
inline AsyncAwaiter<T> operator co_await(AsyncThread<T>&& info)
{
    return AsyncAwaiter(info);
}


template <typename ReturnType>
AsyncThread<ReturnType> do_slow_work(std::function< ReturnType () > &&func){
    return AsyncThread<ReturnType>(std::forward< std::function< ReturnType () > >(func));
}


Result Coroutine() {
    int a = 1;
    auto func =[&]() -> uint64_t{
        // std::cout<< "do a slow work !!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return a;
    };    
    uint64_t result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result1 is  : " << result  << std::endl;  
    a = 2;
    result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result2 is  : " << result  << std::endl; 
    a = 3;
    result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result3 is  : " << result  << std::endl; 
    co_return;
};


void do_work() {
    while (1)
    {
        // 加锁
        // std::cout << "void do_work()  "   << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1)); //！！！！！还有这个加锁要在锁钱前不然，让出cpu后，由于还没有解锁，又会被其他线程再拿到锁，这样就死锁了

        std::lock_guard<std::mutex> g(m);

        // std::cout << " g_work_queue size " << g_resume_queue.size()   << std::endl;

        for(auto task : g_work_queue){
            task->completed();
            g_resume_queue.push_back(task);
        }
        
        // g_resume_queue.assign(g_work_queue.begin(), g_work_queue.end());   //！！！！！！！这里有个大坑坑查了好久，如果连续两次先进来这里，会把g_raw_work_queue中的元素给清理掉，导致后面无法恢复
        g_work_queue.clear();
        // std::cout << " g_resume_queue size " << g_resume_queue.size()   << std::endl;
    }   
    
}

void run_event_loop(){
    std::vector<std::shared_ptr<async_task_base>> g_raw_work_queue_tmp;
    while(1){
        g_raw_work_queue_tmp.clear();
        // std::this_thread::sleep_for(std::chrono::seconds(1)); 
        {
            std::lock_guard<std::mutex> g(m);
            
            // for(auto &task : g_resume_queue){
            //     task->resume();
            // }
            g_raw_work_queue_tmp.swap(g_resume_queue);
        }

        for(auto &task : g_raw_work_queue_tmp){
            task->resume();
        }
    }
}

void test_func(){
    Coroutine();
}

int main(){
    test_func();
    std::thread work_thread(do_work);
    run_event_loop();
}
