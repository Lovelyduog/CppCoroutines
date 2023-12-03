#include <coroutine>
#include <iostream>
 
struct promise;
 
struct coroutine : std::coroutine_handle<promise>
{
    // coroutine(std::coroutine_handle<promise> h): std::coroutine_handle<promise>(h){
    //     std::cout << "coroutine" <<std::endl;
    // }
    ~coroutine(){
        std::cout << "~coroutine" <<std::endl;

    }
    using promise_type = ::promise;
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
    std::suspend_always initial_suspend() noexcept { 
        // std::cout << "~promise" <<std::endl;
        return {}; 
    }
    std::suspend_always final_suspend() noexcept { 
        std::cout << "final_suspend" <<std::endl;
        return {}; 
    }

    // std::suspend_never final_suspend() noexcept { 
    //     std::cout << "final_suspend" <<std::endl;
    //     return {}; 
    // }
    void return_void() {}
    void unhandled_exception() {}
};
 
struct S
{
    int i;
    coroutine f()
    {
        std::cout << i;
        co_return;
    }
};
 
void bad1()
{
    coroutine h = S{0}.f();
    // S{0} destroyed
    h.resume(); // resumed coroutine executes std::cout << i, uses S::i after free
    h.destroy();
}
 
coroutine bad2()
{
    S s{0};
    return s.f(); // returned coroutine can't be resumed without committing use after free
}
 
void bad3()
{
    coroutine h = [i = 0]() -> coroutine // a lambda that's also a coroutine
    {
        std::cout << i;
        co_return;
    }(); // immediately invoked
    // lambda destroyed
    // h.resume(); // uses (anonymous lambda type)::i after free
    // h.destroy();
}
 
void good()
{
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        std::cout << i << std::endl;
        co_return;
        
    }(0);
    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
//                 // frame as a by-value parameter
    h.destroy(); // 如果std::suspend_never final_suspend() ， h.resume();后续 h.resume()会报错，这意味必须使用co_await 该lambda，如果h中使用异步io时，我们需要返回 std::suspend_always
}

int main(){
    good();
    getchar();
}