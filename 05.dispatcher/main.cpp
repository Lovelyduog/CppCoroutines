//
// Created by benny on 2022/3/17.
//
#include "Executor.h"
#include "Task.h"
#include "io_utils.h"
#include "Scheduler.h"
#include <memory>

void test_scheduler() {
  auto scheduler = Scheduler();

  debug("start")
  scheduler.execute([]() { debug("1"); }, 50);
  scheduler.execute([]() { debug("2"); }, 100);
  scheduler.execute([]() { debug("3"); }, 200);
  scheduler.execute([]() { debug("4"); }, 300);
  scheduler.execute([]() { debug("5"); }, 500);
  scheduler.execute([]() { debug("6"); }, 1000);

  scheduler.shutdown();
}

Task<int, AsyncExecutor> simple_task2() {
  debug("task 2 start ...");
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  debug("task 2 returns after 1s.");
  co_return 2;
}

Task<int, NewThreadExecutor> simple_task3() {
  debug("in task 3 start ...");
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  debug("task 3 returns after 2s.");
  co_return 3;
}

Task<int, LooperExecutor> simple_task() {
  debug("task start ...");
  auto result2 = co_await simple_task2();
  debug("returns from task2: ", result2);
  // auto result3 = co_await simple_task3();
  // debug("returns from task3: ", result3);
  // co_return 1 + result2 + result3;
  co_return 1 ;
} 

void test_tasks() {

  // 我改写后的程序
  simple_task().then([](int i) {
    debug("simple task end: ", i);
  }).catching([](std::exception &e) {
    debug("error occurred", e.what());
  }).then([](int i) {
    debug("simple task end2: ", i);
  });

  // auto simpleTask = simple_task();
  // simpleTask.then([](int i) {
  //   debug("simple task end: ", i);
  // }).catching([](std::exception &e) {
  //   debug("error occurred", e.what());
  // });

  sleep(10);
//   try {
//     auto i = simpleTask.get_result();
//     debug("simple task end from get: ", i);
//   } catch (std::exception &e) {
//     debug("error: ", e.what());
//   }
}

int main() {
  test_tasks();

  // auto looper = LooperExecutor();

  // using namespace std::chrono_literals;
  // std::this_thread::sleep_for(1s);
  // looper.shutdown(false);
  // std::this_thread::sleep_for(1s);

  return 0;
}

// ~Task
// 21:53:48.148 [Thread-140515019482688] (main.cpp:41) simple_task: task start ...
// 21:53:48.148 [Thread-140515011089984] (main.cpp:25) simple_task2: task 2 start ...
// 21:53:49.148 [Thread-140515011089984] (main.cpp:28) simple_task2: task 2 returns after 1s.
//  Task(Task &&task)
// ~Task
// ~Task
// 21:53:49.149 [Thread-140515019482688] (main.cpp:43) simple_task: returns from task2:  2
// 21:53:49.149 [Thread-140515019482688] (main.cpp:54) operator(): simple task end:  1
// 21:53:49.149 [Thread-140515019482688] (main.cpp:58) operator(): simple task end2:  1

// 23:03:33.551 [Thread-140231811483200] (main.cpp:41) simple_task: task start ...
// 23:03:33.551 [Thread-140231803090496] (main.cpp:25) simple_task2: task 2 start ...
// 23:03:34.552 [Thread-140231803090496] (main.cpp:28) simple_task2: task 2 returns after 1s.
//  Task(Task &&task)
// ~Task
// ~Task
// 23:03:34.552 [Thread-140231811483200] (main.cpp:43) simple_task: returns from task2:  2
// 23:03:34.552 [Thread-140231811483200] (main.cpp:63) operator(): simple task end:  1
// 23:03:34.552 [Thread-140231811483200] (main.cpp:67) operator(): simple task end2:  1
