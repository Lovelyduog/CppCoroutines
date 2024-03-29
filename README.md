返回值int发coroutine中waiter类型为struct，那该怎么办？
使用awaiter，将awaiter的this指针和对this指针的处理逻辑传递过去，把值赋进去后，再resume
return_value 只会由co_return触发

6.添加异步读写
test-coroutine-order-6.cpp 发现普通文件描述符不能添加到epoll监视集中

7.
把accept 定义为协程函数
asyncread
asynwrite

第五个是目前最完整的文件
5-1 发现了一个死锁问题，reume，添加回原来eventloop队列，会调用await_supend导致死锁
5-2解决了上面的死锁问题 ,同时支持 普通函数resume交给eventloop进行了，以此来尽可能优先

5-3看下，能不能不在await的时候决定恢复策略，而交给协程销毁时？留个疑问，这是合理的做法吗？
看看能不能别在await的时候考虑恢复，通过awaiter或者协程析构时恢复?不可以
表达式在C++20协程中的用法和概念有些细微的差别，相对于您所描述的理解。在C++中，co_await不是用来挂起当前协程并转而执行co_await后面的协程。而是用于挂起当前协程，并等待异步操作（被co_await的操作）完成。当异步操作完成后，协程将会在某个时刻被恢复执行。
不可以在等待体中析构，因为resume -> await_resume -> 从awaiter中获取值返回 ->析构await