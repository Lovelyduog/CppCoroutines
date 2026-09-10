cmake_minimum_required(VERSION 3.18.4)
project(CppCoroutines-Tasks)

set(CMAKE_CXX_STANDARD 20)

add_executable("coroutine-task"
        main.cpp
        io_utils.cpp)
target_link_libraries("coroutine-task" PRIVATE pthread)