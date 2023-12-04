#include <coroutine>
#include <iostream>
#include <future>
#include <chrono>

 
struct promise;
class coroutine;
// struct CoroutineAwaiter;

 
// CoroutineAwaiter operator co_await(coroutine& task) {
//     return CoroutineAwaiter(task);
// }

// struct CoroutineAwaiter 
// {
//     CoroutineAwaiter(coroutine& task):task_(task.from_promise(task.operator std::__n4861::coroutine_handle<void>)){

//     }
//     constexpr bool await_ready() const noexcept { return false; }

//     void await_suspend(std::coroutine_handle<> handle) const noexcept { 
//         std::future<void> result =std::async([=](){
//         using namespace std::chrono_literals;
//         // 模拟两秒后回调触发epoll触发回调
//         std::this_thread::sleep_for(2s);
//         handle.resume();

//         });
//         (void)result;
//     }

//     constexpr void await_resume() const noexcept {}

//     std::coroutine_handle<promise> task_;
// };

struct coroutine : std::coroutine_handle<promise>
{
    // coroutine(std::coroutine_handle<promise> h): std::coroutine_handle<promise>(h){
    //     std::cout << "coroutine" <<std::endl;
    // }
    ~coroutine(){
        std::cout << "~coroutine" <<std::endl;

    }
    using promise_type = ::promise;
    // CoroutineAwaiter operator co_await() {
    //     return CoroutineAwaiter(*this);
    // }

};


struct promise
{
    promise(){
        std::cout << "promise" <<std::endl;
    }
    ~promise(){
        std::cout << "~promise" <<std::endl;

    }
    coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
    // 默认为挂起，如果有co_await std::suspend_nerver会有什么什么问题？不会挂起,不会创建协程对象。
    // co_await 的操作数是 initial_suspend的返回值，如果没有co_await，nerver将直接恢复，always，如果下面没有恢复则不会恢复，可见co_await的目的不是是否挂起，而是是否获取协程返回值
    std::suspend_always initial_suspend() noexcept { 
        // std::cout << "initial_suspend" <<std::endl;
        return {}; 
    }

    // std::suspend_never initial_suspend() noexcept { 
    //     // std::cout << "~promise" <<std::endl;
    //     return {}; 
    // }

    // 如果为alway则需要手动用detory删除promise，因为编译器不知道你在什么时候要resume，所以没有生成删除的代码
    // 这应该是用在异步io上的
    std::suspend_always final_suspend() noexcept { 
        std::cout << "final_suspend" <<std::endl;
        return {}; 
    }

    // 当遇到正常退出(co_return)会自动释放promise;promise构造次数和析构次数 <= coroutine的次数
    // std::suspend_never final_suspend() noexcept { 
    //     std::cout << "final_suspend" <<std::endl;
    //     return {}; 
    // }
    void return_void() {}
    // void return_void() {}
    void unhandled_exception() {}
};


// std::suspend_never initial_suspend() noexcept { 
//     // std::cout << "initial_suspend" <<std::endl;
//     return {}; 
// }
// test代码需要std::suspend_never运行
coroutine test(){
    std::cout << "run test" << std::endl;
    std::suspend_never{};
    std::cout << "run suspend_never" << std::endl;
    std::suspend_always{};
    std::cout << "run suspend_always" << std::endl;
    co_return;
}

coroutine test2(){
    std::cout << "run test2" << std::endl;
    // co_await std::suspend_never{};
    // std::cout << "run suspend_never" << std::endl;
    // co_await std::suspend_always{};
    // std::cout << "run suspend_always" << std::endl;
    co_return;

}

// std::suspend_always initial_suspend() noexcept { 
//     // std::cout << "initial_suspend" <<std::endl;
//     return {}; 
// } 
// test代码需要std::suspend_nalways运行，否则resume会出错
void good()
{
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        std::cout << "run coroutine" << std::endl;
        std::cout << i << std::endl;
        co_return;
        
    }(0);
    // lambda destroyed
    // h.resume(); // no problem, i has been copied to the coroutine
    // std::cout << "main Thread ID: " <<  static_cast<std::size_t>(std::this_thread::get_id()) << std::endl;
    std::future<void> result =std::async([=](){
      using namespace std::chrono_literals;
    //   std::cout << "reume Thread ID: " << std::this_thread::get_id() << std::endl;
      std::this_thread::sleep_for(2s);
      h.resume();
    //   h.resume(); //没法连续resume两次，虽然resume后挂起了
    });
    (void)result;
    // h.destroy(); // 如果std::suspend_never final_suspend() ， h.resume();后续 h.resume()会报错，这意味必须使用co_await 该lambda，如果h中使用异步io时，我们需要返回 std::suspend_always
    std::cout<<"hello" << std::endl; //普通函数无法保存挂起点到协程中

}

coroutine CorWirte(){
    std::future<void> result =std::async([=](){
      using namespace std::chrono_literals;
      //模拟异步写
      std::this_thread::sleep_for(2s);
      std::cout<<"write successfully" << std::endl;
    });
    co_return;
}

void good2()
{

    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        // 这里模拟co_await直到恢复
        coroutine h2 = [](int i) -> coroutine // make i a coroutine parameter
        {
            // co_await CorWirte();
            std::cout<<"post job" << std::endl;
            co_return;
            
        }(0);
        h2.resume();
        co_await std::suspend_always{};
        // co_await CorWirte();
        std::cout<<"write after" << std::endl;
        co_return;
        
    }(0);

    std::future<void> result =std::async([=](){
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(2s);
      h.resume();
    });
    (void)result;
    std::cout<<"hello" << std::endl; //普通函数无法保存挂起点到协程中

}

int main(){
    good2();
    // good2();
    // test();
    // test2();
    getchar();
}