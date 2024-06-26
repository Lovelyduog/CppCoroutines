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

template <>
struct  SuspendStrategy<EnumSuspendStrategy::CommonSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.resume();
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
    //TODO(leo) 确认下执行完挂起，可以用什么检测到？
    SuspendStrategy(std::coroutine_handle<> h){
        // TODO(leo) 写代码测试下是否对主线程效率有帮助
        // destory_queue.push_back(h); 
        h.destroy();
    }
};

// TODO(leo)有没有办法避免多余的awaiter创建
template <typename  ReturnType, bool NeedSuspend = true,  typename SuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend> >
struct suspend_awaiter
{
    using return_type = ReturnType;
    // 是不是可以把task传递出来，把handle保存在Promise中
    suspend_awaiter(return_type value){
        std::cout << "suspend_awaiter(return_type value)" << std::endl;
        value_ = value;
    }



    template <typename U>
    suspend_awaiter(const suspend_awaiter<U>& other) {
        std::cout << "suspend_awaiter(const suspend_awaiter<U>& other) " << std::endl;
        // 这里可以实现具体的类型转换逻辑
        // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
        value_ = static_cast<return_type>(other.GetValue());
    }

    suspend_awaiter(const suspend_awaiter& other) {
        std::cout << "suspend_awaiter(const suspend_awaiter& other)" << std::endl;
        value_ = other.GetValue();
    }


    return_type GetValue(){
        return value_;
    }
    // TODO(leo) 参考boost库中 实现方式 的initail时await_ready返回true，不挂起
    // // TODO（leo）暂时用 必然 挂起,如果希望调度，挂起，否则不挂起，按照程序流走
    // include/boost/outcome/detail/coroutine_support.ipp
     bool await_ready() const noexcept { 
        return false; 
    }
    //  constexpr bool await_ready() const noexcept { return true; }

    void await_suspend(std::coroutine_handle<> h)  {
        SuspendStrategy do_supend(h);
        // h.resume();
        //    std::async([=](){
        //         //挂起当前线程模拟耗时操作
        //         std::this_thread::sleep_for(std::chrono::seconds(1));
        //         h.resume();
        //     });
    }

    return_type await_resume() const noexcept { 
        //  std::cout << "Type of result: " << typeid(a).name() << std::endl;
        // return h_.promise().value_;
        // return typename CoTask::return_type();
        // std::coroutine_handle<promise_type> originalHandle = std::coroutine_handle<promise_type>::from_address(h_.address());
        // auto a = originalHandle.promise().value_;
        // auto a =  h_.promise().value_;
        // auto b =  h_.promise().value_;
        // std::cout << "Type of result: " << typeid(a).name() << std::endl;
        // std::cout << "has value : " << value_ << std::endl;
        return value_;
        //  std::cout << "has_value : " << a.value() << std::endl;  //这个为什么是null
        // std::cout << "await_resume : " << h_.promise().value_ << std::endl;
        // return originalHandle.promise().value_.value_or( typename CoTask::return_type());
        // return task_.value_;
        // return 
    }
    
    // CoTask &task_;
    return_type value_ = return_type();
    bool need_suspend_ = NeedSuspend;
};

struct final_suspend_controler_awaiter
{
    final_suspend_controler_awaiter(){
        std::cout << "final_suspend_controler_awaiter()" << std::endl;
    }
    constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    constexpr void await_resume() const noexcept {} 
};

template <typename ReturnType>
class promise_base{
    virtual ReturnType get_value() = 0;
};

template<typename CoTask>
struct Promise:promise_base< typename CoTask::return_type>
{
    using return_type  = typename CoTask::return_type ;
    bool is_initted_ = false;

    auto initial_suspend() {
        // TODO(leo这个怎么处理)？最先的三个awaiter是哪里来的 initial
        std::cout<< "initial_suspend() " << std::endl;
        return suspend_awaiter<return_type, false>(return_type()); 
    };
    
    // 建议挂起用于区分序列发生器，无限序列发生器永远不会走到这
    final_suspend_controler_awaiter final_suspend() noexcept { 
        std::cout<< "final_suspend() " << std::endl;
        return {}; 
    }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        // std::cout << "get_return_object this :"  << this << std::endl;
        is_initted_ = true; //避免创建多余的awaitable
        return  CoTask(this);
    }

    return_type get_value(){
        return value_;
    }
    // std::suspend_always yield_value(return_type value){

    // }

    void return_value(return_type value){
        value_ = value;
        std::cout<< "return_value " << value << std::endl;
    }

    // 模板化，不然CoroutineTask<int>中没法co_awaitCoroutineTask<char> 
    // template<typename CoTask2>
    // 其实是与promise 类型无关的，感觉还是重载运算符更好点
    // 用于在协程中co_await协程
    
    //协程中挂起协程时做类型转换
    // 这里必须传右值，不然会报错，是否就意味着，这里可以传 协程不希望被拷贝，那不如直接禁止拷贝传参
    template<typename CoTask2>
    suspend_awaiter< typename CoTask2::return_type > await_transform(CoTask2 &&task){
        // 注意这个类型CoTask2 不是该promise对应的CoTask
        std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        // std::cout << "task promise address : " << task.p_ << std::endl;
        // std::cout << "this  : " << this << std::endl;
        return suspend_awaiter<typename CoTask2::return_type>(static_cast<typename CoTask2::promise_type *>(task.p_)->get_value());
    }

    // // template<typename CoTask2>
    // suspend_awaiter<CoTask> await_transform(CoTask task){
    //     return suspend_awaiter<CoTask>();
    // }
    // return_type  value_;
    return_type value_;
};

// TODO(leo) 
// 当在其他线程上调用协程的resume()函数时，协程会在该线程上重新执行被挂起的代码块。这意味着协程的状态会被保存，并且可以在不同的线程间切换执行
// https://stackoverflow.com/questions/75437328/is-it-safe-to-co-await-and-resume-a-coroutine-on-a-different-thread-without-sync
// 是否可以给corouine分配一个线程id，后续挂起时都使用之前task的线程id，这样就可以从协程自身保证有序性？（普通协程）
// 异步执行操作？在i线程中完成后，放回原线程中进行resume ？无锁队列？记录初始线程id？或者ioserviceid?异步池完成操作后放回原来的ioservice中

//TODO(shenlish) 偏特化CoroutineTask<>作为返回值类型为void，可以static_assert来避免使用时用接无返回值的情况
template <typename ReturnType>
struct CoroutineTask{

    using return_type  = ReturnType;
    using promise_type = Promise<CoroutineTask>;

    CoroutineTask(const CoroutineTask &other) = delete;
    CoroutineTask(const CoroutineTask &&other) = delete;
    CoroutineTask& operator=(const CoroutineTask&) = delete;
    CoroutineTask& operator=(const CoroutineTask&&) = delete;
    // 正常挂起不会调用该函数的，这个用于直接获取
    // TODO(leo) 该不该不await直接获取直接获取协程函数的返回值？报警？避免编译通过？如何编译期报错？

    // 没co_await的不应该能获取到coroutine_task,即使获得得到的结果也不一定是对的
    // template <typename U>
    // CoroutineTask(CoroutineTask<U> &other) {
    //     // 这里可以实现具体的类型转换逻辑
    //     // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
    //     // p_ = static_cast<promise_base * >(other.GetPromise());
    //     p_ = other.GetPromise();
    // }
    // 
    // operator ReturnType() const {
    //     return static_cast<promise_type *>(p_)->get_value();
    // }

    // 直接禁止拷贝构造，因为在协程运行的await_transfrom中我们只用到了右值
  

    CoroutineTask(promise_type* promise) {
        // 这里可以实现具体的类型转换逻辑
        // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
        // p_ = static_cast<promise_base * >(other.GetPromise());
        p_ = promise;
        
    }

    void *p_ = nullptr;

};

// template <typename ReturnType>
// struct CoroutineTaskDerived:public CoroutineTask{
//     using return_type  = ReturnType;
//     using promise_type = Promise< CoroutineTask, ReturnType>;
//     std::coroutine_handle<promise_type> handle_;
    
// };



// template <typename ReturnType>
// struct CoroutineTask2{
//     using return_type  = ReturnType;
//     using promise_type = Promise< CoroutineTask, ReturnType>;
//     std::coroutine_handle<promise_type> handle_;
    
// };

// CoroutineTask<int *> three_coroutine(){
//     std::cout << "three_coroutine" << std::endl;
//     co_return nullptr;
// }

CoroutineTask<double> third_coroutine(){
    // co_await three_coroutine();
    std::cout << "third_coroutine end" << std::endl;
    co_return 99.12;
}


CoroutineTask<u_int64_t> second_coroutine(){
    double a = co_await third_coroutine();
    std::cout << "co_await third_coroutine() : " << a << std::endl;
    co_return 3;
}


CoroutineTask<char> first_coroutine(){
    // int a = co_await second_coroutine();
    // second_coroutine();
    // std::cout << "!!!!!!" << std::endl;

    // 不应该在这能直接得到协程的值
    u_int64_t a = co_await second_coroutine();  
    std::cout << " co_await second_coroutine() : "<< std::endl;
    co_return 'b';
}


// CoroutineTask<int> first_coroutine(){
//     co_await second_coroutine();
//     co_return 2;
// }

// TODO(shenglish) 这个为什么是有序的？
// int test_func(int i){
//     std::cout << "# main : " <<  i  << std::endl;
//     // 如果没有恢复，这里返回数据会不对
//     char a = first_coroutine();
//     std::cout << " main" << i << " :" <<  a << std::endl;
// }


// todo(shenglish)使用包装boost异步io write read
int main(){
    // test_func(1);s
    // test_func(2);
    std::cout << "first_coroutine() : "  << std::endl;
    first_coroutine();
    getchar();
}


// 三个协程至少会创建3次awaiter   有两个co_await  在 await_transform 会创建两次awaiter