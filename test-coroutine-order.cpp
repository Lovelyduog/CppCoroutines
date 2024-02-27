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
    SuspendOnOtherThread
};

// Todo(leo)定义一个消息队列，由其他线程消费
std::vector<std::coroutine_handle<> > work_queue;
// 恢复，用户线程处理
std::vector<std::coroutine_handle<> > resume_queue;

// 策略模式
template <enum EnumSuspendStrategy>
struct  SuspendStrategy;


template <>
struct  SuspendStrategy<EnumSuspendStrategy::CommonSuspend>
{
    SuspendStrategy(std::coroutine_handle<> h){
        h.resume();
    }
};


template <>
struct  SuspendStrategy<EnumSuspendStrategy::SuspendOnOtherThread>
{
    SuspendStrategy(std::coroutine_handle<> h){
        work_queue.push_back(h);
    }
};






template <typename  ReturnType, typename SuspendStrategy = SuspendStrategy<EnumSuspendStrategy::CommonSuspend> >
struct initial_suspend_awaiter
{
    using return_type = ReturnType;
    // 是不是可以把task传递出来，把handle保存在Promise中
    initial_suspend_awaiter(return_type value){
        value_ = value;
    }

    template <typename U>
    initial_suspend_awaiter(const initial_suspend_awaiter<U>& other) {
        // 这里可以实现具体的类型转换逻辑
        // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
        value_ = static_cast<return_type>(other.GetValue());
    }

    initial_suspend_awaiter(const initial_suspend_awaiter& other) {
        value_ = other.GetValue();
    }


    return_type GetValue(){
        return value_;
    }
    constexpr bool await_ready() const noexcept { return false; }
    //  constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<> h)  {
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
        std::cout << "has value : " << value_ << std::endl;
        return value_;
        //  std::cout << "has_value : " << a.value() << std::endl;  //这个为什么是null
        // std::cout << "await_resume : " << h_.promise().value_ << std::endl;
        // return originalHandle.promise().value_.value_or( typename CoTask::return_type());
        // return task_.value_;
        // return 
    }
    
    // CoTask &task_;
    return_type value_ = return_type();
};

struct final_suspend_controler_awaiter
{
    constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    constexpr void await_resume() const noexcept {} 
};

// template <typename  ReturnType>
// struct initial_suspend_awaiter< ReturnType,AwaiterType::EnumCommonAwaiter>
// {
//     using return_type = ReturnType;
//     initial_suspend_awaiter(return_type value){
//         value_ = value;
//     }

//     template <typename U>
//     initial_suspend_awaiter(const initial_suspend_awaiter<U>& other) {
//         value_ = static_cast<return_type>(other.GetValue());
//     }

//     initial_suspend_awaiter(const initial_suspend_awaiter& other) {
//         value_ = other.GetValue();
//     }

//     return_type GetValue(){
//         return value_;
//     }
//     constexpr bool await_ready() const noexcept { return false; }

//     constexpr void await_suspend(std::coroutine_handle<> h)  {
//            std::async([=](){
//                 //挂起当前线程模拟耗时操作
//                 std::this_thread::sleep_for(std::chrono::seconds(1));
//                 h.resume();
//             });
//     }

//     return_type await_resume() const noexcept { 
//         std::cout << "has value : " << value_ << std::endl;
//         return value_;
//     }
    
//     return_type value_ = return_type();
// };



template <typename ReturnType>
class promise_base{
    virtual ReturnType get_value() = 0;
};

template<typename CoTask>
struct Promise:promise_base< typename CoTask::return_type>
{
    using return_type  = typename CoTask::return_type ;
    // TODO（leo）暂时用 必然 挂起
    initial_suspend_awaiter<return_type> initial_suspend() { return initial_suspend_awaiter<return_type>(return_type()); };
 
    final_suspend_controler_awaiter final_suspend() noexcept { return {}; }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        std::cout << "get_return_object this :"  << this << std::endl;
        CoTask task;
        task.p_ = this;
        // return {.p = this;}; 
        return  task;
    }

    return_type get_value(){
        return value_;
    }
    // std::suspend_always yield_value(return_type value){

    // }

    void return_value(return_type value){
        value_ = value;
         std::cout<< "return_value " << value << std::endl;
        // std::cout<< "return_value : " << value_.value() << std::endl;
    }

    // 模板化，不然CoroutineTask<int>中没法co_awaitCoroutineTask<char> 
    // template<typename CoTask2>
    // 其实是与promise 类型无关的，感觉还是重载运算符更好点
    template<typename CoTask2>
    initial_suspend_awaiter< typename CoTask2::return_type > await_transform(CoTask2 task){
        // 注意这个类型CoTask2 不是该promise对应的CoTask
        std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        std::cout << "task promise address : " << task.p_ << std::endl;
        std::cout << "this  : " << this << std::endl;
        return initial_suspend_awaiter<typename CoTask2::return_type>(static_cast<typename CoTask2::promise_type *>(task.p_)->get_value());
    }

    // // template<typename CoTask2>
    // initial_suspend_awaiter<CoTask> await_transform(CoTask task){
    //     return initial_suspend_awaiter<CoTask>();
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
    using promise_type = Promise< CoroutineTask>;
    template <typename U>
    CoroutineTask(CoroutineTask<U> other) {
        // 这里可以实现具体的类型转换逻辑
        // 例如，如果 T 和 U 可以相互转换，可以在这里进行相应的转换
        // p_ = static_cast<promise_base * >(other.GetPromise());
        p_ = other.GetPromise();
    }

    CoroutineTask(){
        p_ = nullptr;
    }
    void* GetPromise(){
        return p_;
    }

    // std::coroutine_handle<promise_type> handle_;
    void *p_ = nullptr;
    operator ReturnType() const {
        return static_cast<promise_type *>(p_)->get_value();
    }
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
    int a = second_coroutine();
    std::cout << "!!!!!!" << std::endl;
    // double a = co_await third_coroutine();
    std::cout << " co_await second_coroutine() : " <<  a << std::endl;
    co_return 'b';
}


// CoroutineTask<int> first_coroutine(){
//     co_await second_coroutine();
//     co_return 2;
// }

// TODO(shenglish) 这个为什么是有序的？
int test_func(int i){
    std::cout << "# main : " <<  i  << std::endl;
    // 如果没有恢复，这里返回数据会不对
    char a = first_coroutine();
    std::cout << " main" << i << " :" <<  a << std::endl;
}


// todo(shenglish)使用包装boost异步io write read
int main(){
    test_func(1);
    test_func(2);
    getchar();
}
