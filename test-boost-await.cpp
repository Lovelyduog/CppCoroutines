#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/use_awaitable.hpp>
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
    initial_suspend_awaiter(return_type value){
        value_ = value;
    }

    template <typename U>
    initial_suspend_awaiter(const initial_suspend_awaiter<U>& other) {
        value_ = static_cast<return_type>(other.GetValue());
    }

    return_type GetValue(){
        return value_;
    }
    constexpr bool await_ready() const noexcept { return false; }
    constexpr void await_suspend(std::coroutine_handle<> h)  {
           std::async([=](){
                //挂起当前线程模拟耗时操作
                std::this_thread::sleep_for(std::chrono::seconds(1));
                h.resume();
            });
    }

    return_type await_resume() const noexcept { 
        std::cout << "has value : " << value_ << std::endl;
        return value_;
    }
    
    return_type value_ = return_type();
};

struct final_suspend_controler_awaiter
{
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
    initial_suspend_awaiter<CoTask> initial_suspend() { return initial_suspend_awaiter<CoTask>(return_type()); };
 
    final_suspend_controler_awaiter final_suspend() noexcept { return {}; }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        std::cout << "get_return_object this :"  << this << std::endl;
        CoTask task;
        task.p_ = this;
        return  task;
    }

    return_type get_value(){
        return value_;
    }

    void return_value(return_type value){
        value_ = value;
         std::cout<< "return_value " << value << std::endl;
    }

    template<typename CoTask2>
    initial_suspend_awaiter<CoTask2> await_transform(CoTask2 task){
        std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        std::cout << "task promise address : " << task.p_ << std::endl;
        std::cout << "this  : " << this << std::endl;
        return initial_suspend_awaiter<CoTask2>(static_cast<typename CoTask2::promise_type *>(task.p_)->get_value());
    }

    return_type value_;
};

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


    void *p_ = nullptr;
    operator ReturnType() const {
        return static_cast<promise_type *>(p_)->get_value();
    }
};

CoroutineTask<double> third_coroutine(){
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



boost::asio::awaitable<void> async_read_operation(boost::asio::ip::tcp::socket& socket)
{
    std::vector<char> buffer(1024);

    try
    {
        std::size_t bytesRead = co_await socket.async_read_some(
            boost::asio::buffer(buffer), boost::asio::use_awaitable);
        
        std::cout << "Read " << bytesRead << " bytes: ";
        std::cout.write(buffer.data(), bytesRead);
        std::cout << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error while reading data: " << e.what() << std::endl;
    }
}

int main()
{
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::socket socket(ioContext);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::loopback(), 12345);
    
    socket.connect(endpoint);

    boost::asio::co_spawn(ioContext, async_read_operation(socket), boost::asio::detached);

    ioContext.run();

    return 0;
}