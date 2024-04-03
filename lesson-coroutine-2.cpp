
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

    // 当时initial_suspend返回的awaiter时，挂起，直接resume
    bool await_ready() const noexcept { 
        return false;
    }

    //也可以直接恢复 
    // std::coroutine_handle<> await_suspend(std::coroutine_handle<> h)  {
    //     return h;
    // }

    void await_suspend(std::coroutine_handle<> h)  {
        // std::cout <<"await_suspend()" << std::endl;
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

    // 当时initial_suspend返回的awaiter时，挂起，跳过await_suspend，直接resume,跳过
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



// 必须为noexcept，因为这个时候协程已经运行结束，不该有异常产生
template <typename CoTask>
struct CommonAwaiter <CoTask, EnumAwaiterType::EnumFinal>
{
    CommonAwaiter(){
    }

    // 这里不选择true让编译器帮我们自动释放,如果为true编译器不知道什么时候协程结束，无法帮助我们优化
    bool await_ready() noexcept { 
        return false;
    }


    void await_suspend(std::coroutine_handle<> h)  noexcept{
        h_ = h;
        g_event_loop_queue.emplace_back(std::shared_ptr<async_task_base>( new coroutine_task<CoTask, EnumAwaiterType::EnumFinal>(*this)));
    }

    // 无需返回
    void await_resume()  noexcept{ 
    }

    std::coroutine_handle<> h_ = nullptr;
};


template<typename CoTask>
struct Promise
{
    using return_type  = typename CoTask::return_type ;
    ~Promise(){
    //    std::cout << "~Promise" << std::endl;
    }
    CommonAwaiter<CoTask, EnumAwaiterType::EnumInitial> initial_suspend() {
        return {}; 
    };
    
    CommonAwaiter<CoTask, EnumAwaiterType::EnumFinal> final_suspend() noexcept { 
        return {}; 
    }

    // 提供了一种对协程中未捕获的异常的再处理，比如将异常保存下来，实现协程如以下形式 ： coroutine().get().catch()
    // 这里我们的实现形式决定了，这里直接再次抛出异常就好
    void unhandled_exception(){
        // try {
        std::rethrow_exception(std::current_exception());
        // } catch (const std::exception& e) {
        //     // 输出异常信息
        //     std::cerr << "Unhandled exception caught in CustomAsyncTask: " << e.what() << std::endl;
        // } catch (...) {
        //     std::cerr << "Unhandled unknown exception caught in CustomAsyncTask!" << std::endl;
        // }
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
   
    // 该代码写在Promise中的好处是，可以方便阅读代码很容易就能回想出协程最多会返回三个等待体
    template<typename T>
    CommonAwaiter<CoroutineTask<T>> await_transform(CoroutineTask<T> &&task){
        return CommonAwaiter<CoroutineTask<T>>(task.p_);
    }

    CoTask await_transform(CoTask &&task){
        return CommonAwaiter<CoTask>(task.p_);
    }


    return_type value_;
};

template <typename ReturnType>
struct CoroutineTask{

    using return_type  = ReturnType;
    using promise_type = Promise<CoroutineTask>;

    CoroutineTask(const CoroutineTask &other) = delete;
    CoroutineTask(const CoroutineTask &&other) = delete;
    CoroutineTask& operator=(const CoroutineTask&) = delete;
    CoroutineTask& operator=(const CoroutineTask&&) = delete;

    CoroutineTask(promise_type* promise) {
        p_ = promise;
        
    }

    promise_type *p_ = nullptr;

};



CoroutineTask<u_int64_t> second_coroutine(){
    co_return 3;
}

CoroutineTask<float> third_coroutine(){
    co_return 3.1;
}


CoroutineTask<char> first_coroutine(){
    uint64_t num =  co_await second_coroutine();
    std::cout << "second_coroutine result is  : " << num  << std::endl; 
    float num2 =  co_await third_coroutine();
    std::cout << "third_coroutine result is  : " << num2  << std::endl; 
    co_return 'b';
}


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
        
        // 优先恢复耗时任务
        for(auto &task : g_raw_work_queue_tmp){
            task->resume();
        }

        for(auto task : g_event_loop_queue_temp){
            task->resume();
        }

    }
}


void test_func(){
    first_coroutine();
}

int main(){
    test_func();
    std::thread work_thread(do_work);
    run_event_loop();
    return 0;
}
