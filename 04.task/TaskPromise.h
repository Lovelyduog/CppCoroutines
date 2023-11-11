//
// Created by benny on 2022/3/17.
//

#ifndef CPPCOROUTINES_TASKS_04_TASK_TASKPROMISE_H_
#define CPPCOROUTINES_TASKS_04_TASK_TASKPROMISE_H_

#include <functional>
#include <mutex>
#include <list>
#include <optional>
#include <condition_variable>

#include "coroutine_common.h"
#include "Result.h"
#include "TaskAwaiter.h"

template<typename ResultType>
class Task;

template<typename ResultType>
struct TaskPromise {
  // suspend_always 会有问题，他会一直
  // std::suspend_never initial_suspend() { return {}; }
  // TaskAwaiter<ResultType> initial_suspend() { return {}; }
  // 这里必须返回一个awaitable
  TaskAwaiter<ResultType> initial_suspend() { return TaskAwaiter<ResultType>(1); }

  // 这个为nerver 会有问题
  // TODO(leo) 完善区分机制
  TaskAwaiter<ResultType> final_suspend() noexcept { return TaskAwaiter<ResultType>(2); }

  Task<ResultType> get_return_object() {
    return Task{std::coroutine_handle<TaskPromise>::from_promise(*this)};
  }

  // 形式参数为co_await的对象 如果为1，则为int。如果时协程函数，则为协程；如果co_await后为等待体，则直接为等待体
  // 这个在co_await时调用
  template<typename _ResultType>
  TaskAwaiter<_ResultType> await_transform(Task<_ResultType> &&task) {
    return TaskAwaiter<_ResultType>(std::move(task)); //新标准是不是可以用exchange呢？
  }

  void unhandled_exception() {
    std::lock_guard lock(completion_lock);
    result = Result<ResultType>(std::current_exception());
    completion.notify_all();
    notify_callbacks();
  }

  void return_value(ResultType value) {
    std::lock_guard lock(completion_lock);
    result = Result<ResultType>(std::move(value));
    completion.notify_all();
    notify_callbacks();
  }

  ResultType get_result() {
    // blocking for result or throw on exception
    std::unique_lock lock(completion_lock);
    if (!result.has_value()) {
      completion.wait(lock);
    }
    return result->get_or_throw();
  }

  void on_completed(std::function<void(Result<ResultType>)> &&func) {
    std::unique_lock lock(completion_lock);
    if (result.has_value()) {
      auto value = result.value();
      lock.unlock();
      func(value);
    } else {
      completion_callbacks.push_back(func);
    }
  }

 private:
  std::optional<Result<ResultType>> result;

  std::mutex completion_lock;
  std::condition_variable completion;

  std::list<std::function<void(Result<ResultType>)>> completion_callbacks;

  void notify_callbacks() {
    auto value = result.value();
    for (auto &callback : completion_callbacks) {
      callback(value);
    }
    completion_callbacks.clear();
  }

};

#endif //CPPCOROUTINES_TASKS_04_TASK_TASKPROMISE_H_
