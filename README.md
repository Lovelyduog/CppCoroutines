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
common协程挂起直接设置为ready  true 就可以，这样co_await一个协程时，实际上不用做任何挂起动作，即不参与调度
设置为false，后续执行可以参与调度，让某些已经挂起完成恢复的协程优先恢复执行，感觉这样更加合理，可以尽可能的先到先服务

TODO(leo)
后面向办法共用一个resume队列(即让resume队列成为eventloop队列)
使用条件变量，当do_resume消费完了，通知await_suspend中的以及do_resume中的添加消费者到resume队列中？好像现在用互斥锁一样不会出现死锁，可以添加到同一个队列中，切记resume不能在锁未打开之前reume
去掉final awaiter


目前 7 是最佳实践