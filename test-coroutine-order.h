#include <coroutine>

// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;

template<typename T>
struct MetaResult;


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

    // TODO(leo)initial_suspend_awaiter 和 final_suspend_controler_awaiter那个的await_resume应该返回MetaResult?? 我觉得应该是在这里
    // 这里的返回类型也应该是
    constexpr void await_resume() const noexcept {}
};

// 这个是最终co_await返回
// 该挂起的携程状态不能够resume
// TODO(leo)final_suspend返回的final_suspend_controler_awaiter不会执行resume?????
struct final_suspend_controler_awaiter
{
    // 挂起
    // 可以返回任何值，只要支持到bool的隐式转换
    constexpr bool await_ready() const noexcept { return false; }

    // 必须返回void  这里 保存coroutine_handle的把作用应该不是为了恢复。挂起的作用，是不是可以提高吞吐率？用户请求高发期，尽快相应请求，当用户请求少时，删除释放协程体，当然也可以加上限策略来删除。这里可以将handle移交给删除线程
    constexpr void await_suspend(std::coroutine_handle<>) const noexcept {}

    // 可以返回非void类型
    // 这里的返回类型应该是 MetaResult?是这里还是上面的？这里应该不是返回值的地方，地方，因为该处已经执行到co_return后面了
    // TODO(leo)如果挂起，这个函数是否有机会被调用？好像这个点不能够resume,会有未定义的错误发生
    /*TODO（leo）initial_suspend 返回的协程可以调用resume，但是结果是未定义的？但是还是可以resume的，那是不是可以在这里await_resume里摧毁协程对象，
    resume的存在，可以使initial_suspend_awaiter和final_suspend_controler_awaiter用同样的方式resume，但是执行两种不同的操作，前者await_resume 是返回值，后者是销毁协程对象
    */
    constexpr void await_resume() const noexcept {} 
};

// 可以支持下隐式转换
// T 这个T应该是CoTask::return_type才对？
template<typename T>
struct MetaResult{

    // 构造函数
    MetaResult(T val) : value(val) {}

    // 转换运算符，将MetaResult<T>隐式转换为T
    operator T() const {
        return value;
    }

    // Todo(leo) 支持迭代器
    T value;
};

template<typename CoTask>
struct Promise
{
    using return_type  = typename CoTask::return_type ;
    // TODO（leo）暂时用必然挂起
    std::suspend_always initial_suspend() { return {}; };
 
    // 销毁promise_type后调用 final_suspend,这两个函数主要作用是返回等待体
    std::suspend_always final_suspend() noexcept { return {}; }

    // return_type 引用时传引用还是穿值，这个应该不挂起？
    // 这个需要是
    std::suspend_always yield_value(return_type value){

    }

    void return_value(return_type )

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
    
    // 需要对yield挂起点和co_await分开处理，一个是迭代
    // 如果想yield和co_await共存的话，挂起前可能需要知道yield是否为空，如果非空，则返回一个可迭代对象，或者一个结构体

    // 作为和promise沟通的纽带
    std::coroutine_handle<promise_type> handle_;
    
};