//
// Created by benny on 2022/3/17.
//

#ifndef CPPCOROUTINES_04_TASK_TASK_H_
#define CPPCOROUTINES_04_TASK_TASK_H_

#include "coroutine_common.h"
#include "TaskPromise.h"

template<typename ResultType, typename Executor = NewThreadExecutor>
struct Task {

  using promise_type = TaskPromise<ResultType, Executor>;

  ResultType get_result() {
    return handle.promise().get_result();
  }

  Task &then(std::function<void(ResultType)> &&func) {
    handle.promise().on_completed([func](auto result) {
      try {
        func(result.get_or_throw());
      } catch (std::exception &e) {
        // ignore.
      }
    });
    return *this;
  }

  Task &catching(std::function<void(std::exception &)> &&func) {
    handle.promise().on_completed([func](auto result) {
      try {
        result.get_or_throw();
      } catch (std::exception &e) {
        func(e);
      }
    });
    return *this;
  }

  Task &finally(std::function<void()> &&func) {
    handle.promise().on_completed([func](auto result) { func(); });
    return *this;
  }

  explicit Task(std::coroutine_handle<promise_type> handle) noexcept: handle(handle) {}

  Task(Task &&task) noexcept: handle(std::exchange(task.handle, {})) {std::cout << " Task(Task &&task)" << std::endl;}

  Task(Task &) = delete;

  Task &operator=(Task &) = delete;

  ~Task() {
    std::cout << "~Task"  << std::endl;
    // if (handle) handle.destroy();
    //  https://stackoverflow.com/questions/68352718/is-it-necessary-to-call-destroy-on-a-stdcoroutine-handle 是否有必要手动销毁？
    // 无需
    // When the coroutine state is destroyed either because it terminated via co_return or uncaught exception, or because it was destroyed via its handle, it does the following:
    // calls the destructor of the promise object.
    // calls the destructors of the function parameter copies.
    // calls operator delete to free the memory used by the coroutine state.
    // transfers execution back to the caller/resumer
    
    //  handle.destroy()释放的是Task，而Task会在co_return后自行析构

  }

 private:
  // https://stackoverflow.com/questions/68352718/is-it-necessary-to-call-destroy-on-a-stdcoroutine-handle
  // https://en.cppreference.com/w/cpp/coroutine/coroutine_handle/destroy
  std::coroutine_handle<promise_type> handle;
};

#endif //CPPCOROUTINES_04_TASK_TASK_H_
