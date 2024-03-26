
#include <coroutine>
#include <future>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>  
#include <unordered_map>

template <typename T>
class Singleton {
public:
    static T& getInstance() {
        if (!instance_){
            instance_ = new T();
        }
        return *instance_;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton) = delete;

protected:
    Singleton() = default;
    ~Singleton() = default;
private:
    static T *instance_;
};

template <typename T>
T *Singleton<T>::instance_ = nullptr;


enum EnumAsyncIO {
    // EnumUndefine = -1,
    EnumAsyncIOWrite = 0,
    EnumAsyncIORead = 1,
    EnumAsyncIOClose = 2,
    EnumAllNUM = 3
};


std::mutex m;
// std::mutex m2;
// std::condition_variable cv;

template <enum EnumAsyncIO>
struct  AsyncIOStrategy;

// 前置类型声明不能带默认类型采纳数
template <EnumAsyncIO Enum, typename ReturnType>
struct  AsyncIO;

// 前置类型声明
template <typename ReturnType>
struct CoroutineTask;

template<typename CoTask>
struct Promise;

class file_descriptor;

template <EnumAsyncIO, typename ReturnType>
struct AsyncIOAwaiter;

// 传CoTask的好处是，可以根据协程状态选择awaiter是否挂起协程
// return_value 只会由co_return触发，所以这个只是对挂起协程使用的awaiter
template <typename CoTask>
struct suspend_awaiter
{
    using return_type =  typename CoTask::return_type;
    using promise_type = typename CoTask::promise_type;
    // 是不是可以把task传递出来，把handle保存在Promise中
    // template <typename ReturnType2>
    suspend_awaiter(promise_type* promise){
        promise_ = promise;
    }

    // 当时initial_suspend返回的awaiter时，挂起，直接resume
    bool await_ready() const noexcept { 
        return !promise_->is_initted();
    }


    void await_suspend(std::coroutine_handle<> h)  {
        // 这里直接恢复，也可以交给eventloop进行调度恢复
       h.resume();
    }

    return_type await_resume() const noexcept { 
        return promise_->get_value();
    }
    
    promise_type* promise_;
};

struct final_suspend_controler_awaiter
{
    final_suspend_controler_awaiter(){
    }
    constexpr bool await_ready() const noexcept { return true; }

    constexpr void await_suspend(std::coroutine_handle<> h) const noexcept {

    }

    constexpr void await_resume() const noexcept {} 
};

template <typename T>
struct AsyncAwaiter;


template <typename ReturnType>
struct  AsyncThread
{
    using return_type = ReturnType;

    AsyncThread(std::function<return_type ()>&& func): func_(func){

    }
    std::function<return_type ()> func_;
};


//TODO(leo) base目前没起到作用
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
        return suspend_awaiter<CoTask>(this); 
    };
    
    final_suspend_controler_awaiter final_suspend() noexcept { 
        return {}; 
    }
    void unhandled_exception(){}
    CoTask get_return_object(){ 
        return  CoTask(this);
    }

    return_type get_value() override{
        return value_;
    }


    bool is_initted()  override{
        return is_initted_;
    }

    void return_value(return_type value){
        is_initted_ = true;
        value_ = value;
    }


    // TODO(leo)这个和promise 无关是不是从类内一处来比较好？
    // 这个没必要被返回类型为awaiter 替代掉，方便已经定义协程，添加到另外一个协程中await

    template<typename T>
    AsyncAwaiter<T> await_transform(AsyncThread<T> &&info){
        // std::cout << "AsyncAwaiter<T> await_transform(AsyncThread<T> &&info)" << std::endl;

        return AsyncAwaiter<T>(info);
    }
   
    // TODO(leo)如何确定走哪个await_transform ，如果上面的在下面 有问题
    template<typename CoTask2>
    suspend_awaiter<CoTask2> await_transform(CoTask2 &&task){

        // std::cout<< "await_transform " << (static_cast<typename CoTask2::promise_type *>(task.p_)->get_value()) << std::endl;
        return suspend_awaiter<CoTask2>(task.p_);
    }
    // template<typename T>
    // AsyncAwaiter<T> await_transform(AsyncAwaiter<T> &&awaiter){

    //     return awaiter;
    // }

    // template<Enum， typename T>
    // AsyncIOAwaiter<AsyncIO<T>::async_io_type, T> await_transform(AsyncIO<T> &&info){
    //     return AsyncIOAwaiter <T>::async_io_type, T>(info);
    // }

    template<EnumAsyncIO Enum,typename T>   
    AsyncIOAwaiter<Enum, T> await_transform(AsyncIO<Enum, T> &&info){
        return AsyncIOAwaiter <Enum, T>(info);
    }
    return_type value_;
};

// template<typename T>
// inline AsyncAwaiter<T> operator co_await(AsyncThread<T>& info)
// {
//     return AsyncAwaiter(info);
// }


// TODO(leo) p_是不是可以不是void类型
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

    promise_type *p_ = nullptr;

};

class async_task_base;

template <typename ReturnType>
class async_task;

template <typename ReturnType>
class AsyncThread;

// Todo(leo)定义一个消息队列，由其他线程消费
std::vector<std::shared_ptr<async_task_base>> g_raw_work_queue; //原来的 eventloop队列
std::vector<std::shared_ptr<async_task_base>> g_work_queue; //执行耗时操作线程队列

template <typename ReturnType>
struct AsyncAwaiter
{
    using return_type = ReturnType;

    AsyncAwaiter(AsyncThread<ReturnType>& info){
        value_ = return_type{};
        func_ = info.func_;
    }



    bool await_ready() const noexcept { 
        // 是不是可以在这里获取线程，获取线程失败，则直接在当前线程恢复？
        return false; 
    }

    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        // std::cout << " void await_suspend(std::coroutine_handle<> h)" << std::endl;
        std::lock_guard<std::mutex> g(m);
        g_work_queue.emplace_back(std::shared_ptr<async_task_base>( new async_task<uint64_t>(*this)));
    }

    return_type await_resume() const noexcept { 
        return value_;
    }
    std::function<return_type ()> func_;
    std::coroutine_handle<> h_;
    return_type value_ = return_type();
};




struct async_task_base
{
    virtual void completed() = 0;
    virtual void resume() = 0;
};

// TODO(leo)这个可以加上超时机制
template <typename ReturnType>
struct async_task: public async_task_base{
    async_task(AsyncAwaiter<ReturnType> &awaiter)
    :owner_(awaiter)
    {

    }

    void completed() override{
        ReturnType result = owner_.func_();
        owner_.value_ = result;
    }

    void resume() override{
        // std::cout << "async_task ::  resume ############" << std::endl;
        owner_.h_.resume();
    }
    AsyncAwaiter<ReturnType> &owner_ ;
    // std::function< typename ReturnType ()> do_func_;
};




// ========================================================================================================================
/*TODO(leo)天机协程做异步写，是哟个异步写的文件文件描述符存到await在,close后，添加到协程中，
最后统一从协程对象中移除？或者在awaiter销毁时从epoll中移除？不能再await析构中，可能会多次从epoll中移除。需要需要关闭的fd

*/


namespace 
{
    

    void set_nonblocking(int fd){

        int ops = fcntl(fd, F_GETFL);
        if(ops < 0){
            perror("int ops = fcntl(fd, F_GETFL)");
        }

        ops |= O_NONBLOCK;

        if(fcntl(fd, F_SETFL, ops)){
            perror("fcntl(fd, F_SETFL, ops)");
        }
    }
} 



using AsyncIOStrategyWrite = AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOWrite>;
//TODO(leo)可以加queue可指定
using AsyncIOStrategyWriteIORead = AsyncIOStrategy<EnumAsyncIO::EnumAsyncIORead>;
using AsyncIOStrategyWriteClose = AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOClose>;

// template <typename ReturnType>
// class promise_base;


// TODO(leo)策略是否需要包含移交给epoll还是说移交仅仅交给awaiter?
// 等下需要实现AsyncIO 到 awaiter的转换，以及awaiter和epoll的交互

struct file_descriptor
{
    int  fd_ = -1;
    bool need_remove_from_epoll_ =false;
    struct epoll_event events_;
    
    file_descriptor(int fd){
        fd_ = fd;
        bzero(&events_, sizeof(events_));
        events_.data.fd = fd_;
    }
};



template <>
struct  AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOWrite>
{
    AsyncIOStrategy(file_descriptor& fd, void *buf, size_t n):fd_(fd),buf_(buf),num_(n){
        set_nonblocking(fd_.fd_);
        fd_.need_remove_from_epoll_ = true;
        fd_.events_.events |= EPOLLOUT;
    }

    int complete(){
       return write(fd_.fd_, buf_, num_);
    }
    size_t num_;
    void *buf_;
    file_descriptor &fd_;
};

template <>
struct  AsyncIOStrategy<EnumAsyncIO::EnumAsyncIORead>
{
    AsyncIOStrategy(file_descriptor& fd, void *buf, size_t n):fd_(fd),buf_(buf),num_(n){
        set_nonblocking(fd_.fd_);
        fd_.need_remove_from_epoll_ = true;
        fd_.events_.events |= EPOLLOUT;
    }

    int complete(){
       return read(fd_.fd_, buf_, num_);
    }

    size_t num_;
    void *buf_;
    file_descriptor &fd_;
};

template <>
struct  AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOClose>
{
    AsyncIOStrategy(file_descriptor& fd):fd_(fd){
        fd_.need_remove_from_epoll_ = true;
        fd_.events_.events |= EPOLLIN;
    }

    int complete(){
       int ret = close(fd_.fd_);
       if(ret >0 )
       {
         fd_.need_remove_from_epoll_ = false;
       }
       return ret;
    }
    file_descriptor &fd_;
};

//返回值默认为int
// template <  template < enum EnumAsyncIO >  typename IoStrategy = AsyncIOStrategy, typename ReturnType = int>
template <EnumAsyncIO Enum, typename ReturnType = int>
struct  AsyncIO
{;
    using return_type = ReturnType;

    AsyncIO(file_descriptor &fd, void *buf, size_t n):stragtegy_(fd, buf, n){

    }

    AsyncIOStrategy<Enum>   stragtegy_;
};

template <typename ReturnType>
struct  AsyncIO<EnumAsyncIO::EnumAsyncIOClose, ReturnType>
{
    using return_type = ReturnType;

    AsyncIO(file_descriptor &fd):stragtegy_(fd){

    }
    // file_descriptor &fd_;
    AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOClose>  stragtegy_;
};


AsyncIO<EnumAsyncIO::EnumAsyncIOWrite,int> AsyncWrite(file_descriptor &fd, void *buf, size_t n){
    return  AsyncIO<EnumAsyncIO::EnumAsyncIOWrite,int>(fd, buf, n);
}

AsyncIO<EnumAsyncIO::EnumAsyncIORead,int> AsyncRead(file_descriptor &fd,void *buf, size_t n){
    return  AsyncIO<EnumAsyncIO::EnumAsyncIORead,int>(fd, buf, n);
}

AsyncIO<EnumAsyncIO::EnumAsyncIOClose,int> AsyncClose(file_descriptor &fd){
    return  AsyncIO<EnumAsyncIO::EnumAsyncIOClose,int>(fd);
}


file_descriptor create_fd(const char *path, int mode){
    int fd = open(path, O_CREAT | O_RDWR, mode);
    if (fd == -1) {
        perror("open");
    }

    return file_descriptor(fd);
}



#define  MAX_EPOLL_EVENT_NUM 1024

void do_work() {
    while (1)
    {
        std::lock_guard<std::mutex> g(m);

        for(auto task : g_work_queue){
            task->completed();
            g_raw_work_queue.push_back(task);
        }
        g_work_queue.clear();
    }   
    
}

void do_reume(){
    std::lock_guard<std::mutex> g(m);
    
    for(auto &task : g_raw_work_queue){
        task->resume();
    }
    g_raw_work_queue.clear();
}




struct event_loop
{
public:
    event_loop():work_thread_(do_work){
        
        epoll_fd_ = epoll_create(MAX_EPOLL_EVENT_NUM);
    }

    void post(std::function<void ()>&& func){
        event_list_.emplace_back(func);
    }

    // 将await
    // TODO(leo)这里暂时不考虑性能问题
    // template<enum EnumAsyncIO, typename ReturnType>
    // void epoll_add(AsyncIOAwaiter<EnumAsyncIO::EnumAsyncIOClose, ReturnType>& awaiter){
    //     if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &event) == -1) {
                
    //         // 如果文件描述符已存在，errno将被设置为EEXIST
    //         if (errno == EEXIST) {
    //             printf("File descriptor %d already added, modifying.\n", fd);
    //             awaiter.
    //             // 修改已存在的文件描述符的事件
    //             if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event) == -1) {
    //                 printf("Failed to modify file descriptor %d: %s\n", fd, strerror(errno));
    //                 // 这里需要进行错误处理
    //             }
    //         } else {
    //             printf("Failed to add file descriptor %d: %s\n", fd, strerror(errno));
    //             // 这里需要进行错误处理
    //         }
    //     }
    // }

    void run(){
        struct epoll_event  events[MAX_EPOLL_EVENT_NUM] = {};

        while (1)
        {
            // TODO(leo)time out设置
            int nfds = epoll_wait(epoll_fd_, events, MAX_EPOLL_EVENT_NUM, 1);


            if (nfds == -1) {
                perror("epoll_wait failed\n");
                exit(EXIT_FAILURE);
            }
            for(auto & func : event_list_ ){
                func();
            }
            event_list_.clear();
            for (int n = 0; n < nfds; ++n) {
                struct epoll_event & event = events[n];
                async_task_base * task_ptr =  static_cast<async_task_base *>(event.data.ptr);
                assert(task_ptr);
                task_ptr->completed();
                task_ptr->resume();
            }
            do_reume();

        }
        work_thread_.join();
        getchar();
    }

    int epoll_fd_;



private:
    std::thread work_thread_;

    std::vector<std::function<void ()> > event_list_;
};

// 使用继承多态 传给epoll避免类型恢复的问题
template <EnumAsyncIO Enum, typename ReturnType>
struct AsyncIOAwaiter:public async_task_base
{
    // using async_io_awaiter_type = Enum;
    using return_type = ReturnType;

    AsyncIOAwaiter(AsyncIO<Enum, ReturnType>& info):stragtegy_(info.stragtegy_){
        value_ = return_type{};
    }



    bool await_ready() const noexcept { 
        return false; 
    }

    // 是不是可以从协程获取eventloop，协程创建使用iocontext
    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        struct epoll_event &event = stragtegy_.fd_.events_;
        int fd = stragtegy_.fd_.fd_;
        event.data.ptr = this;
        event_loop &loop =  Singleton<event_loop>::getInstance();
        if (epoll_ctl(loop.epoll_fd_, EPOLL_CTL_ADD, fd, &event) == -1) {
                
            //TODO(leo) 后续完善异常处理
            // 如果文件描述符已存在，errno将被设置为EEXIST
            if (errno == EEXIST) {
                printf("File descriptor %d already added, modifying.\n", fd);
                    
                // 修改已存在的文件描述符的事件
                if (epoll_ctl(loop.epoll_fd_, EPOLL_CTL_MOD, fd, &event) == -1) {
                    printf("Failed to modify file descriptor %d: %s\n", fd, strerror(errno));
                }
            } else {
                printf("Failed to add file descriptor %d: %s\n", fd, strerror(errno));
                // 这里需要进行错误处理
            }
        }


    }

    return_type await_resume() const noexcept { 
        return value_;
    }

    //实现接口epoll返回时调用
    void completed() override{
        ReturnType result = stragtegy_.complete();
        value_ = result;
    }

    void resume() override{
        // std::cout << "async_task ::  resume ############" << std::endl;
        h_.resume();
    }

    std::coroutine_handle<> h_;;

    return_type value_ = return_type();
    AsyncIOStrategy<Enum>   stragtegy_;

};


template <typename ReturnType>
struct AsyncIOAwaiter<EnumAsyncIO::EnumAsyncIOClose, ReturnType>:public async_task_base
{
    // using async_io_awaiter_type = Enum;
    using return_type = ReturnType;

    AsyncIOAwaiter(AsyncIO<EnumAsyncIO::EnumAsyncIOClose, ReturnType>& info):stragtegy_(info.fd_){
        value_ = return_type{};
    }



    bool await_ready() const noexcept { 
        return false; 
    }

    void await_suspend(std::coroutine_handle<> h)  {
        h_ = h;
        
        // 是不是要移交给epoll处理呢？
    }

    return_type await_resume() const noexcept { 
        return value_;
    }
    std::coroutine_handle<> h_;;

    return_type value_ = return_type();
    AsyncIOStrategy<EnumAsyncIO::EnumAsyncIOClose>   stragtegy_;
};



// TODO(leo)这个类保存awaiter，添加到epoll监视集合的ptr中，epoll出发后，执行任务
// template <enum EnumAsyncIO, typename ReturnType>
// struct async_io_task: public async_task_base{
//     async_task(AsyncIOAwaiter<EnumAsyncIO, ReturnType> &awaiter)
//     :owner_(awaiter)
//     {

//     }

//     void completed() override{
//         ReturnType result = owner_;
//         owner_.value_ = result;
//     }

//     void resume() override{
//         // std::cout << "async_task ::  resume ############" << std::endl;
//         owner_.h_.resume();
//     }
//     AsyncAwaiter<ReturnType> &owner_ ;
//     // std::function< typename ReturnType ()> do_func_;
// };

CoroutineTask<u_int64_t> second_coroutine(){
    co_return 3;
}

template <typename ReturnType>
AsyncThread<ReturnType> do_slow_work(std::function< ReturnType () > &&func){
    
    // 必须使用完美转发
    return AsyncThread<ReturnType>(std::forward< std::function< ReturnType () > >(func));
}


// 该函数用于验证c++重载
char do_slow_work(std::function<char () > &&func){
    
    // 必须使用完美转发
    return 'c';
}


CoroutineTask<char> first_coroutine(){
    auto func =[]() -> uint64_t{
        std::cout<< "do a slow work !!!!!!!!!!!!!!!!!!!!!" << std::endl;
        return 1;
    };    
    uint64_t result = co_await do_slow_work<uint64_t>(func);
    // if(result == 1){
    //     std::cout << " resumed successfully " << std::endl;
    //     exit(1);
    // }
    
    std::cout << "@@@@@@@@@ result is  : " << result  << std::endl; 
    file_descriptor file =  create_fd("./test.file", 777);
    const char * buf = "hello world\n";
    int num = co_await AsyncWrite(file, (void *)buf, sizeof(buf));
    std::cout << "@@@@@@@@@ num is  : " << num  << std::endl; 
    co_return 'b';
}

void test_func(){
    first_coroutine();
}



int main(){
    event_loop &loop = Singleton<event_loop>::getInstance();
    loop.post(test_func);
    loop.run();
    
}


// 如果一个线程在文件描述符中写，而另一个线程在同时关闭了同一文件描述符，可能会引发潜在的问题。
// 这种情况下，可能会导致写操作失败或产生异常（例如文件描述符无效或已关闭），从而造成不确定的行为。
// 因此，在多线程操作中，需要谨慎管理文件描述符的生命周期，以避免出现不一致的状态。
// 非如阻塞，如果a线程在写，b线程也想写入，则会报错