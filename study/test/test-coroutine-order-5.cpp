
#include <coroutine>
#include <future>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>

std::mutex m;
// std::mutex m2;
// std::condition_variable cv;


// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;


enum class EnumSuspendStrategy:uint32_t{
    CommonSuspend ,
    OtherThreadSuspend,
    FinishSuspend
};



// 策略模式
template <enum EnumSuspendStrategy>
struct  SuspendStrategy;

using CommonSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend>;
//TODO(leo)可以加queue可指定
using OtherThreadSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::OtherThreadSuspend>;
using FinishSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::FinishSuspend>;

// template <typename ReturnType>
// class promise_base;

template<typename CoTask>
struct Promise;

template <>
struct  SuspendStrategy<EnumSuspendStrategy::CommonSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.resume();
    }
};



template <>
struct  SuspendStrategy<EnumSuspendStrategy::FinishSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.destroy();
    }
};

// 传CoTask的好处是，可以根据协程状态选择awaiter是否挂起协程
// return_value 只会由co_return触发，所以这个只是对挂起协程使用的awaiter
template <typename CoTask,  typename SuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend> >
struct suspend_awaiter
{
    using return_type =  typename CoTask::return_type;
    using promise_type = typename CoTask::promise_type;
    // 是不是可以把task传递出来，把handle保存在Promise中
    // template <typename ReturnType2>
    suspend_awaiter(promise_type* promise){
        promise_ = promise;
    }

    // 当时initial_suspend返回的awaiter时，挂起，直接resume
    bool await_ready() const noexcept { 
        return !promise_->is_initted();
    }


    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
    }

    return_type await_resume() const noexcept { 
        return promise_->get_value();
    }
    ~suspend_awaiter(){
        std::cout <<"~suspend_awaiter()" << std::endl;
        if(h_ != nullptr){
            h_.resume();
        }
    }
    promise_type* promise_;
    std::coroutine_handle<> h_ = nullptr;
};

struct final_suspend_controler_awaiter
{
    final_suspend_controler_awaiter(){
    }
    constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<> h) const noexcept {

    }

    constexpr void await_resume() const noexcept {} 
};

template <typename T>
struct AsyncAwaiter;


template <typename ReturnType>
struct  AsyncThread
{
    using return_type = ReturnType;

    AsyncThread(std::function<return_type ()>&& func): func_(func){

    }
    std::function<return_type ()> func_;
};


//TODO(leo) base目前没起到作用
template <typename ReturnType>
class promise_base{
public:
    virtual ReturnType get_value() = 0;
    virtual bool is_initted() = 0;
};

template<typename CoTask>
struct Promise:promise_base< typename CoTask::return_type>
{
    using return_type  = typename CoTask::return_type ;
    bool is_initted_ = false;

    auto initial_suspend() {
        return suspend_awaiter<CoTask>(this); 
    };
    
    final_suspend_controler_awaiter final_suspend() noexcept { 
        return {}; 
    }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        return  CoTask(this);
    }

    return_type get_value() override{
        return value_;
    }


    bool is_initted()  override{
        return is_initted_;
    }

    void return_value(return_type value){
        is_initted_ = true;
        value_ = value;
    }


    // TODO(leo)这个和promise 无关是不是从类内一处来比较好？
    // 这个没必要被返回类型为awaiter 替代掉，方便已经定义协程，添加到另外一个协程中await

    template<typename T>
    AsyncAwaiter<T> await_transform(AsyncThread<T> &&info){
        // std::cout << "AsyncAwaiter<T> await_transform(AsyncThread<T> &&info)" << std::endl;

        return AsyncAwaiter<T>(info);
    }
   
    // TODO(leo)如何确定走哪个await_transform ，如果上面的在下面 有问题
    template<typename CoTask2>
    suspend_awaiter<CoTask2> await_transform(CoTask2 &&task){

        // std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        return suspend_awaiter<CoTask2>(task.p_);
    }
    // template<typename T>
    // AsyncAwaiter<T> await_transform(AsyncAwaiter<T> &&awaiter){

    //     return awaiter;
    // }

   


    return_type value_;
    std::coroutine_handle<> h_;
};

// template<typename T>
// inline AsyncAwaiter<T> operator co_await(AsyncThread<T>& info)
// {
//     return AsyncAwaiter(info);
// }


// TODO(leo) p_是不是可以不是void类型
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

class async_task_base;

template <typename ReturnType>
class async_task;

template <typename ReturnType>
class AsyncThread;

// Todo(leo)定义一个消息队列，由其他线程消费
std::vector<std::shared_ptr<async_task_base>> g_raw_work_queue; //原来的 eventloop队列
std::vector<std::shared_ptr<async_task_base>> g_work_queue; //执行耗时操作线程队列

template <typename ReturnType>
struct AsyncAwaiter
{
    using return_type = ReturnType;

    AsyncAwaiter(AsyncThread<ReturnType>& info){
        value_ = return_type{};
        func_ = info.func_;
    }



    bool await_ready() const noexcept { 
        // 是不是可以在这里获取线程，获取线程失败，则直接在当前线程恢复？
        return false; 
    }

    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        // std::cout << " void await_suspend(std::coroutine_handle<> h)" << std::endl;
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

struct async_task_base
{
    virtual void completed() = 0;
    virtual void resume() = 0;
};

// TODO(leo)这个可以加上超时机制
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
        // std::cout << "async_task ::  resume ############" << std::endl;
        owner_.h_.resume();
    }
    AsyncAwaiter<ReturnType> &owner_ ;
    // std::function< typename ReturnType ()> do_func_;
};


CoroutineTask<u_int64_t> second_coroutine(){
    co_return 3;
}

// template<typename T>
// inline AsyncAwaiter<T> operator co_await(AsyncThread<T>& info)
// {
//     return AsyncAwaiter(info);
// }

// uint64_t hard_working()  {
//     std::cout<< "do a slow work !!!!!!!!!!!!!!!!!!!!!" << std::endl;
//     return 1;
// };

// 模拟耗时操作
// TODO(leo)AsyncThread返回值根据传入的func返回值获取
//TODO(leo)试一下alambda从外部传参给do_slow_work
template <typename ReturnType>
AsyncThread<ReturnType> do_slow_work(std::function< ReturnType () > &&func){
    
    // 必须使用完美转发
    return AsyncThread<ReturnType>(std::forward< std::function< ReturnType () > >(func));
}

CoroutineTask<char> first_coroutine(){
    auto func =[]() -> uint64_t{
        // std::cout<< "do a slow work !!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return 1;
    };    
    // std::cout << "before  co_await do_slow_work " << std::endl; 
    uint64_t result = co_await do_slow_work<uint64_t>(func);
    if(result == 1){
        std::cout << " resumed successfully " << std::endl;
        // exit(1);
    }
    std::cout << "@@@@@@@@@ result is  : " << result  << std::endl; 
    // std::cout << "！！！！！ result  is : " << result << std::endl; //这一行不是原子的
    co_return 'b';
}


void do_work() {
    while (1)
    {
        // 加锁
        // std::cout << "void do_work()  "   << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); //！！！！！还有这个加锁要在锁钱前不然，让出cpu后，由于还没有解锁，又会被其他线程再拿到锁，这样就死锁了

        std::lock_guard<std::mutex> g(m);

        // std::cout << " g_work_queue size " << g_raw_work_queue.size()   << std::endl;

        for(auto task : g_work_queue){
            task->completed();
            g_raw_work_queue.push_back(task);
        }
        
        // g_raw_work_queue.assign(g_work_queue.begin(), g_work_queue.end());   //！！！！！！！这里有个大坑坑查了好久，如果连续两次先进来这里，会把g_raw_work_queue中的元素给清理掉，导致后面无法恢复
        g_work_queue.clear();
        // std::cout << " g_raw_work_queue size " << g_raw_work_queue.size()   << std::endl;
    }   
    
}

void do_reume(){
    // std::cout << "void do_reume()" << std::endl;
    std::lock_guard<std::mutex> g(m);
    
    for(auto &task : g_raw_work_queue){
        task->resume();
    }
    g_raw_work_queue.clear();
}

void test_func(){
    first_coroutine();
}

int main(){
    test_func();
    std::thread work_thread(do_work);
    // work_thread.detach();

    // std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // 主线程每秒从处理好的异步任务池中获取协程进行resume
    while (1)
    {
        do_reume();
        // 每隔1秒取一次完成的异步任务
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    work_thread.join();
    getchar();
    
}
