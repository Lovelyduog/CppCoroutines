返回值int发coroutine中waiter类型为struct，那该怎么办？
使用awaiter，将awaiter的this指针和对this指针的处理逻辑传递过去，把值赋进去后，再resume
return_value 只会由co_return触发

6.添加异步读写
test-coroutine-order-6.cpp 发现普通文件描述符不能添加到epoll监视集中

7.
把accept 定义为协程函数
asyncread
asynwrite