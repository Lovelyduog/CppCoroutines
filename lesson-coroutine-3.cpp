
#include <coroutine>
#include <functional>
#include <chrono>
#include <iostream>
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
std::vector<std::shared_ptr<async_task_base>> g_event_loop_queue; 
std::vector<std::shared_ptr<async_task_base>> g_resume_queue; //多线程异步任务完成后后，待主线程恢复的线程
std::vector<std::shared_ptr<async_task_base>> g_work_queue; //执行耗时操作线程队列

enum class EnumAwaiterType:uint32_t{
    EnumInitial = 1, //协程initial
    EnumSchduling = 2,// 用户co_await
    EnumFinal = 3//销毁
};


template <typename ReturnType>
struct CoroutineTask;

template <typename CoTask, EnumAwaiterType AwaiterType >
struct CommonAwaiter ;

template <typename>
struct AsyncAwaiter;


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
        ReturnType result = owner_.func_();
        owner_.value_ = result;
    }

    void resume() override{
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

    bool await_ready() const noexcept { 
        return false; 
    }
    
    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        std::lock_guard<std::mutex> g(m);
        g_work_queue.emplace_back(std::shared_ptr<async_task_base>( new async_task<uint64_t>(*this)));
    }

    return_type await_resume() const noexcept { 
        return value_;
    }

  
    std::function<return_type ()> func_;
    std::coroutine_handle<> h_; 
    return_type value_ = return_type();
};


template <typename CoTask, EnumAwaiterType AwaiterType>
struct coroutine_task: public async_task_base{
    coroutine_task(CommonAwaiter<CoTask, AwaiterType> &awaiter)
    :owner_(awaiter)
    {

    }

    void completed() override{
    }

    void resume() override{
        if(owner_.h_.done()){
            owner_.h_.destroy();
        }else{
            owner_.h_.resume();
        }
    }
    CommonAwaiter<CoTask,AwaiterType> &owner_ ;
};

template <typename CoTask, EnumAwaiterType AwaiterType = EnumAwaiterType::EnumSchduling>
struct CommonAwaiter 
{
    using return_type =  typename CoTask::return_type;
    using promise_type = typename CoTask::promise_type;
    CommonAwaiter(promise_type* promise):promise_(promise){
    }

    bool await_ready() const noexcept { 
        return false;
    }

    //也可以直接恢复 
    // std::coroutine_handle<> await_suspend(std::coroutine_handle<> h)  {
    //     return h;
    // }

    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        g_event_loop_queue.emplace_back(std::shared_ptr<async_task_base>( new coroutine_task<CoTask, AwaiterType>(*this)) );
    }


    return_type await_resume() const noexcept { 
        return promise_->get_value();
    }

    ~CommonAwaiter(){
    }

    bool resume_ready_= false;
    promise_type* promise_ = nullptr;
    std::coroutine_handle<> h_ = nullptr;
};


template <typename CoTask>
struct CommonAwaiter<CoTask, EnumAwaiterType::EnumInitial>
{
    CommonAwaiter(){
    }

    bool await_ready() const noexcept { 
        return true;
    }

    void await_suspend(std::coroutine_handle<>)  {
    }

    void await_resume() const noexcept { 
    }

    ~CommonAwaiter(){
    }
};



template <typename CoTask>
struct CommonAwaiter <CoTask, EnumAwaiterType::EnumFinal>
{
    CommonAwaiter(){
    }

    bool await_ready() noexcept { 
        return false;
    }

    void await_suspend(std::coroutine_handle<> h)  noexcept{
        h_ = h;
        g_event_loop_queue.emplace_back(std::shared_ptr<async_task_base>( new coroutine_task<CoTask, EnumAwaiterType::EnumFinal>(*this)));
    }

    void await_resume()  noexcept{ 
    }

    std::coroutine_handle<> h_ = nullptr;
};


template<typename CoTask>
struct Promise
{
    using return_type  = typename CoTask::return_type ;
    ~Promise(){
    }
    CommonAwaiter<CoTask, EnumAwaiterType::EnumInitial> initial_suspend() {
        return {}; 
    };
    
    CommonAwaiter<CoTask, EnumAwaiterType::EnumFinal> final_suspend() noexcept { 
        return {}; 
    }

    void unhandled_exception(){
        std::rethrow_exception(std::current_exception());
    }

    CoTask get_return_object(){ 
        return  CoTask(this);
    }

    return_type get_value() {
        return value_;
    }


    void return_value(return_type value){
        value_ = value;
    }
   
    template<typename T>
    CommonAwaiter<CoroutineTask<T>> await_transform(CoroutineTask<T> &&task){
        return CommonAwaiter<CoroutineTask<T>>(task.p_);
    }

  
    template<typename T>
    inline AsyncAwaiter<T> await_transform(AsyncThread<T>&& info)
    {
        return AsyncAwaiter(info);
    }



    return_type value_;
};

template <typename ReturnType>
struct CoroutineTask{

    using return_type  = ReturnType;
    using promise_type = Promise<CoroutineTask>;

    CoroutineTask(const CoroutineTask &other) = delete;
    CoroutineTask(const CoroutineTask &&other) = delete;
    CoroutineTask& operator=(const CoroutineTask&) {};
    CoroutineTask& operator=(const CoroutineTask&&) = delete;

    CoroutineTask(promise_type* promise) {
        p_ = promise;
        
    }

    promise_type *p_ = nullptr;

};


void do_work() {
    while (1)
    {
        std::lock_guard<std::mutex> g(m);
        for(auto task : g_work_queue){
            task->completed();
            g_resume_queue.push_back(task);
        }
        
        g_work_queue.clear();
    }   
    
}

void run_event_loop(){
    std::vector<std::shared_ptr<async_task_base>> g_raw_work_queue_tmp;
    std::vector<std::shared_ptr<async_task_base>> g_event_loop_queue_temp;
    while(1){
        g_raw_work_queue_tmp.clear();
        g_event_loop_queue_temp.clear();
        {
            g_event_loop_queue_temp.swap(g_event_loop_queue);
            std::lock_guard<std::mutex> g(m);
            g_raw_work_queue_tmp.swap(g_resume_queue);
        }
        
        for(auto &task : g_raw_work_queue_tmp){
            task->resume();
        }

        for(auto task : g_event_loop_queue_temp){
            task->resume();
        }

    }
}


// ------------------------------------------------------------------------------------------------------



template <typename ReturnType>
AsyncThread<ReturnType> do_slow_work(std::function< ReturnType () > &&func){
    return AsyncThread<ReturnType>(std::forward< std::function< ReturnType () > >(func));
}


CoroutineTask<u_int64_t> second_coroutine(){
    co_return 3;
}

CoroutineTask<float> third_coroutine(){
    co_return 3.1;
}


CoroutineTask<char> first_coroutine(){
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
    uint64_t num =  co_await second_coroutine();
    std::cout << "@@@@@@@@@ second_coroutine result is  : " << num  << std::endl; 
    a = 3;
    result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result3 is  : " << result  << std::endl;  
    float num2 =  co_await third_coroutine();
    a = 4;
    result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ third_coroutine result is  : " << num2  << std::endl; 
    result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result4 is  : " << result  << std::endl;  
    co_return 'b';
}


CoroutineTask<char> Coroutine(){
    int a = 1;
    auto func =[&]() -> uint64_t{
        // std::cout<< "do a slow work !!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return a;
    };  
    uint64_t result = co_await do_slow_work<uint64_t>(func);
    std::cout << "@@@@@@@@@ result is  : " << result  << std::endl; 
    uint64_t num =  co_await second_coroutine();
    std::cout << "@@@@@@@@@ coroutine result is  : " << num  << std::endl; 

    co_return 'b';
}


void test_func(){
    Coroutine();
    first_coroutine();
}

int main(){
    test_func();
    std::thread work_thread(do_work);
    run_event_loop();
    return 0;
}
