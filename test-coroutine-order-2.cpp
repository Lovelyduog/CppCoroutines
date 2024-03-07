#include <coroutine>
#include <future>
#include <chrono>
#include <iostream>
#include <optional>
#include <vector>

// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;


enum class EnumSuspendStrategy:uint32_t{
    CommonSuspend ,
    OtherThreadSuspend,
    FinishSuspend
};

// Todo(leo)定义一个消息队列，由其他线程消费
std::vector<std::coroutine_handle<> > work_queue;
// 恢复，用户线程处理
std::vector<std::coroutine_handle<> > resume_queue;
// destory queue 可以让协程的销毁交给其他线程，提高主线程处理效率
std::vector<std::coroutine_handle<> > destory_queue;

  


// 策略模式
template <enum EnumSuspendStrategy>
struct  SuspendStrategy;

using CommonSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend>;
using OtherThreadSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::OtherThreadSuspend>;
using FinishSuspendStrategy = SuspendStrategy<EnumSuspendStrategy::FinishSuspend>;

template <typename ReturnType>
class promise_base;


template <>
struct  SuspendStrategy<EnumSuspendStrategy::CommonSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.resume();
        // resume_queue.push_back(h);
        // std::cout << "resume_queue.push_back(h) size : " << resume_queue.size() << std::endl;
    }
};


template <>
struct  SuspendStrategy<EnumSuspendStrategy::OtherThreadSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        work_queue.push_back(h);
    }
};


template <>
struct  SuspendStrategy<EnumSuspendStrategy::FinishSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.destroy();
    }
};

template <typename  ReturnType, bool NeedSuspend = true,  typename SuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend> >
struct suspend_awaiter
{
    using return_type = ReturnType;
    // 是不是可以把task传递出来，把handle保存在Promise中
    // template <typename ReturnType2>
    suspend_awaiter(return_type value, promise_base<return_type>* promise){
        std::cout << "suspend_awaiter(return_type value)" << std::endl;
        value_ = value;
        promise_ = promise;
    }



    template <typename U>
    suspend_awaiter(const suspend_awaiter<U>& other) {
        std::cout << "suspend_awaiter(const suspend_awaiter<U>& other) " << std::endl;
        value_ = static_cast<return_type>(other.GetValue());
    }

    suspend_awaiter(const suspend_awaiter& other) {
        std::cout << "suspend_awaiter(const suspend_awaiter& other)" << std::endl;
        value_ = other.GetValue();
    }


    return_type GetValue(){
        return value_;
    }

    // 当时initial_suspend返回的awaiter时，挂起，直接resume
    bool await_ready() const noexcept { 
        // return false; 
        std::cout << "await_ready is_initted : " << promise_->is_initted() <<  std::endl;
        return !promise_->is_initted();
    }

    // void await_suspend(std::coroutine_handle<> h)  {
    //     std::cout << "await_suspend(std::coroutine_handle<> h)" << std::endl;
    //     SuspendStrategy do_supend(h);
    // }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<> h)  {
        std::cout << "await_suspend" << std::endl;
        return h;
    }

    return_type await_resume() const noexcept { 
        std::cout << "await_resume" << std::endl;
        return value_;
    }
    
    return_type value_ = return_type();
    bool need_suspend_ = NeedSuspend;
    promise_base<return_type> *promise_;
};

template <typename  ReturnType, bool NeedSuspend = true,  typename SuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend> >
struct suspend_controler_awaiter
{
    using return_type = ReturnType;
    // 是不是可以把task传递出来，把handle保存在Promise中
    suspend_controler_awaiter(return_type value){
        // std::cout << "suspend_controler_awaiter(return_type value)" << std::endl;
        value_ = value;
    }

    suspend_controler_awaiter(){
        // std::cout << "suspend_awaiter(return_type value)" << std::endl;
        std::cout << "suspend_controler_awaiter()" << std::endl;
        value_ = return_type{};
    }


    return_type GetValue(){
        return value_;
    }

    bool await_ready() const noexcept { 
        
        return false; 
    }

    void await_suspend(std::coroutine_handle<> h)  {
        std::cout << "await_suspend(std::coroutine_handle<> h)" << std::endl;
        // SuspendStrategy do_supend(h);
        resume_queue.push_back(h);
    }

    return_type await_resume() const noexcept { 
        std::cout << "await_resume" << std::endl;
        return value_;
    }
    
    return_type value_ = return_type();
    bool need_suspend_ = NeedSuspend;
};

struct final_suspend_controler_awaiter
{
    final_suspend_controler_awaiter(){
        std::cout << "final_suspend_controler_awaiter()" << std::endl;
    }
    constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<> h) const noexcept {

    }

    constexpr void await_resume() const noexcept {} 
};

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
        std::cout<< "initial_suspend() " << std::endl;
        return suspend_awaiter<return_type, false>(return_type(), this); 
    };
    
    final_suspend_controler_awaiter final_suspend() noexcept { 
        std::cout<< "final_suspend() " << std::endl;
        return {}; 
    }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        // is_initted_ = false; 
        return  CoTask(this);
    }

    return_type get_value() override{
        is_initted_ = true;
        return value_;
    }


    bool is_initted()  override{
        return is_initted_;
    }

    void return_value(return_type value){
        value_ = value;
        std::cout<< "return_value " << value << std::endl;
    }


    // TODO(leo)这个和promise 无关是不是从类内一处来比较好？
    // 这个没必要被返回类型为awaiter 替代掉，方便已经定义协程，添加到另外一个协程中await
    template<typename CoTask2>
    suspend_awaiter< typename CoTask2::return_type > await_transform(CoTask2 &&task){

        std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        return suspend_awaiter<typename CoTask2::return_type>(static_cast<typename CoTask2::promise_type *>(task.p_)->get_value(),  static_cast<typename CoTask2::promise_type *>(task.p_));
    }
    template<typename T>
    suspend_controler_awaiter<T> await_transform(suspend_controler_awaiter<T> &&awaiter){

        return suspend_controler_awaiter<T>(awaiter.value_);
    }
   

    // suspend_awaiter<int> await_transform(int a){

    //     std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
    //     return suspend_awaiter<typename CoTask2::return_type>(static_cast<typename CoTask2::promise_type *>(task.p_)->get_value());
    // }

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

    void *p_ = nullptr;

};

int test_func(){
    return 1;
}

// TODO(leo) 
// 协程co_await  返回值为awaiter的函数而不是co_wait协程函数

CoroutineTask<double> third_coroutine(){
    std::cout << "！！third_coroutine end" << std::endl;
    co_return 99.12;
}


CoroutineTask<u_int64_t> second_coroutine(){
    double a = co_await third_coroutine();
    // 到这直接co_await一个awaiter
    // co_await std::suspend_always{};
    std::cout << "！！co_await third_coroutine() : " << a << std::endl;
    co_return 3;
}


CoroutineTask<char> first_coroutine(){
    std::cout << "！！ co_await suspend_controler_awaiter() berfore: "  << std::endl;
    co_await suspend_controler_awaiter<char>{};
    std::cout << "！！ co_await suspend_controler_awaiter() end: "  << std::endl;
    u_int64_t a = co_await second_coroutine(); 
     std::cout << "！！ co_await second_coroutine() : " << a << std::endl; 
    co_await suspend_controler_awaiter<char>{};
    std::cout << "！！ co_await second_coroutine() : end2 !!!!"  << std::endl;
    co_return 'b';
}



int main(){
    std::cout << "！！first_coroutine() : "  << std::endl;
    first_coroutine();
    std::cout << "resume_queue size :  "  << resume_queue.size()  << std::endl;
    for (auto& h : resume_queue)
    {
        std::cout << " ========= "    << std::endl;
        h.resume();
        // getchar();
    }


    resume_queue[0].resume(); //上面resume后又会添加到resume_queue中


    // 
    // resume_queue[0].resume(); //TODO(leo) 是可不可以不挂起？前三个为initial suspend挂起导致的？
    // resume_queue[1].resume();
    // resume_queue[2].resume();
    // resume_queue[3].resume();
    // resume_queue[4].resume();

    // if (resume_queue[4].done()){
    //     std::cout<< "hello" << std::endl;
    // }

    //  resume_queue[4].resume();





    // resume_queue[5].resume();
    // std::cout << "resume_queue size :  "  << resume_queue.size()  << std::endl;
    // resume_queue[1].resume();
    // std::cout << "resume_queue size :  "  << resume_queue.size()  << std::endl;
    // resume_queue[2].resume();
    
    getchar();
}
