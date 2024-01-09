#include <coroutine>
#include <future>
#include <chrono>
#include <iostream>
#include <optional>
// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;


template <typename  CoTask>
struct initial_suspend_awaiter
{
    using return_type = typename CoTask::return_type;
    using promise_type = typename CoTask::promise_type;
    // 是不是可以把task传递出来，把handle保存在Promise中
    initial_suspend_awaiter(){
    }

    constexpr bool await_ready() const noexcept { return false; }
    //  constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<> &&h)  {
        h_ = h;
    //    std::async([=](){
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
            h_.resume();
        // });
    }

    CoTask::return_type await_resume() const noexcept { 
        //  std::cout << "Type of result: " << typeid(a).name() << std::endl;
        // return h_.promise().value_;
        // return typename CoTask::return_type();
        std::coroutine_handle<promise_type> originalHandle = std::coroutine_handle<promise_type>::from_address(h_.address());
        auto a = originalHandle.promise().value_;
        auto b =  a.has_value();
        std::cout << "Type of result: " << typeid(a).name() << std::endl;
        std::cout << "has_value : " << b << std::endl;
        //  std::cout << "has_value : " << a.value() << std::endl;  //这个为什么是null
        // return originalHandle.promise().value_.value_or( typename CoTask::return_type());
        // return task_.value_;
        // return 
    }

    // CoTask &task_;
    std::coroutine_handle<> h_;
};

struct final_suspend_controler_awaiter
{
    constexpr bool await_ready() const noexcept { return false; }

    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    constexpr void await_resume() const noexcept {} 
};

template<template <typename> typename CoTask1, typename ReturnType>
struct Promise
{
    using return_type  = ReturnType ;
    using CoTask = CoTask1<ReturnType>;
    // TODO（leo）暂时用 必然 挂起
    initial_suspend_awaiter<CoTask> initial_suspend() { return initial_suspend_awaiter<CoTask>(); };
 
    final_suspend_controler_awaiter final_suspend() noexcept { return {}; }
    void unhandled_exception(){}
    CoTask get_return_object(){ return {}; }

    // std::suspend_always yield_value(return_type value){

    // }

    void return_value(return_type value){
        value_ = value;
        std::cout<< "return_value : " << value_.value() << std::endl;
    }

    // 模板化，不然CoroutineTask<int>中没法co_awaitCoroutineTask<char> 
    template<typename CoTask2>
    initial_suspend_awaiter<CoTask2> await_transform(CoTask2 task){
        return initial_suspend_awaiter<CoTask2>();
    }

    // // template<typename CoTask2>
    // initial_suspend_awaiter<CoTask> await_transform(CoTask task){
    //     return initial_suspend_awaiter<CoTask>();
    // }
    // return_type  value_;
    std::optional<return_type> value_;
};

template <typename ReturnType>
struct CoroutineTask{
    using return_type  = ReturnType;
    using promise_type = Promise< CoroutineTask, ReturnType>;
    std::coroutine_handle<promise_type> handle_;
    
};

template <typename ReturnType>
struct CoroutineTask2{
    using return_type  = ReturnType;
    using promise_type = Promise< CoroutineTask, ReturnType>;
    std::coroutine_handle<promise_type> handle_;
    
};

CoroutineTask<int *> three_coroutine(){
    std::cout << "three_coroutine" << std::endl;
    co_return nullptr;
}

CoroutineTask<int> second_coroutine(){
    // co_await three_coroutine();
    std::cout << "second_coroutine" << std::endl;
    co_return 1;
}
CoroutineTask2<char> first_coroutine(){
    int a = co_await second_coroutine();
    std::cout << a << std::endl;
    co_return 'b';
}


// CoroutineTask<int> first_coroutine(){
//     co_await second_coroutine();
//     co_return 'b';
// }

int main(){
    // first_coroutine();
    first_coroutine();
    getchar();
}
