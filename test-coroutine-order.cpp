#include <coroutine>

// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;


// 第一个目标：实现同时何以yield和await的协程：单线程版本的
// normal 函数
// async 对象
// TODO(leo) 模板 suspend_controler
// TODO(leo)yield 和co_await 能不能一起用，如果想yield 和 await 一起用的话，不是该
// 协程体的销毁都认为控制，即final_suspend时挂起 ，这样有利于编译优化
template <typename  CoTask>
struct initial_suspend_awaiter
{
    initial_suspend_awaiter(CoTask task){
        // 可以间接通过task来到promise
    }
    // 在这里决定是否挂起，可以减少await_suspend生成的代码
    constexpr bool await_ready() const noexcept { return true; }

    // TODO(leo) 普通携程，无异步逻辑，可以直接恢复
    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    // 
    constexpr void await_resume() const noexcept {}
};

// 该挂起的携程状态不能够resume
struct final_suspend_controler_awaiter
{
    // 挂起
    constexpr bool await_ready() const noexcept { return false; }

    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    constexpr void await_resume() const noexcept {}
};

template<typename CoTask>
struct Promise
{
    using return_type  = typename CoTask::return_type ;
    // TODO（leo）暂时用必然挂起
    std::suspend_always initial_suspend() { return {}; };
 
    // 销毁promise_type后调用 final_suspend,这两个函数主要作用是返回等待体
    std::suspend_always final_suspend() noexcept { return {}; }

    // return_type 引用时传引用还是穿值
    std::suspend_always yield_value(return_type value){

    }

    // TODO(leo)转换为awaitable
    // CoroutineTask 类型trait
    std::suspend_always await_transform(CoTask task){

    }

    

};


// TODO(leo)需要有个定义返回值类型的地方
// return_type由这里指定吧
template <typename ReturnType>
struct CoroutineTask{
    using return_type  = ReturnType;
    using promise_type = Promise<CoroutineTask>;
    // TODO(leo)支持迭代器遍历
    // TODO(leo)task调函数，往挂起中添加，如果时yield
    
    // 需要对yield挂起点和co_await分开处理吗？

    // 作为和promise沟通的纽带
    std::coroutine_handle<promise_type> handle_;
    
};