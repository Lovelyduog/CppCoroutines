//
// Created by benny on 2022/3/17.
//

#ifndef CPPCOROUTINES_04_TASK_TASKAWAITER_H_
#define CPPCOROUTINES_04_TASK_TASKAWAITER_H_

#include "coroutine_common.h"
#include <iostream>

template<typename ResultType>
struct Task;

template<typename Result>
struct TaskAwaiter {
  explicit TaskAwaiter(Task<Result> &&task) noexcept
      : task(std::move(task)) {}

  TaskAwaiter(TaskAwaiter &&completion) noexcept
      : task(std::exchange(completion.task, {})) {}

  TaskAwaiter(int flag) {std::cout << "sadasd" << std::endl; is_null = flag;}


  TaskAwaiter(TaskAwaiter &) = delete;

  TaskAwaiter &operator=(TaskAwaiter &) = delete;

  // 在这个示例中该函数根本没用上
  constexpr bool await_ready() const noexcept {
    return is_null == 1;
    // return true;//直接挂起，是不是可以更具某些条件选择是否挂起
  }

  // 等待体挂起，则传入该挂其点的reume到协程体中
  void await_suspend(std::coroutine_handle<> handle) noexcept {
    std::cout << "await_suspend" <<  std::endl;
    if (is_null == 1 or is_null == 2){
      return;
    }

    task.finally([handle]() {
      handle.resume();
    });
  }

  Result await_resume() noexcept {
    std::cout << "await_resume" <<  std::endl;
    if(is_null == 1 or is_null == 2){
      return {};
    }
    return task.get_result();
  }


 private:
  bool is_need_suspend ;
  int is_null = 0;
  Task<Result> task;
};

#endif //CPPCOROUTINES_04_TASK_TASKAWAITER_H_
