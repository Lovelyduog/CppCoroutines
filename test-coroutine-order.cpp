#include <coroutine>
#include <future>
#include <chrono>

// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;


template <typename  CoTask>
struct initial_suspend_awaiter
{
    using return_type = typename CoTask::return_type;
    // 是不是可以把task传递出来，把handle保存在Promise中
    initial_suspend_awaiter(){
    }

    constexpr bool await_ready() const noexcept { return false; }
    //  constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<return_type > h)  {
        // std::async([=](){
        //     std::this_thread::sleep_for(std::chrono::seconds(2));
        //     h.resume();
        // });
        h_ = h;
    }

    CoTask::return_type await_resume() const noexcept { 
        return h_.promise().value_;
    }
    std::coroutine_handle<return_type> h_;
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
    }

    // 模板化，不然CoroutineTask<int>中没法co_awaitCoroutineTask<char> 
    template<typename CoTask>
    initial_suspend_awaiter<CoTask> await_transform(CoTask task){
        return initial_suspend_awaiter<CoTask>();
    }
    return_type  value_;
};

template <typename ReturnType>
struct CoroutineTask{
    using return_type  = ReturnType;
    using promise_type = Promise< CoroutineTask, ReturnType>;
    std::coroutine_handle<promise_type> handle_;
    
};

CoroutineTask<int> second_coroutine(){
    co_return 1;
}

CoroutineTask<char> first_coroutine(){
    co_await second_coroutine();
    co_return 'b';
}

int main(){
    first_coroutine();
    getchar();
}
