cmake_minimum_required(VERSION 3.20)
project(CppCoroutines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(Threads REQUIRED)

# 未来协程库的公开头文件；库名与命名空间定下后在此扩充
add_library(cppcoroutines INTERFACE)
target_include_directories(cppcoroutines INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 依赖 boost 的学习程序，等 thirdparty 引入 boost（或改用 standalone asio）后再编译
set(CC_SKIPPED_SOURCES
    test-boost-await.cpp
    test-boost-client.cpp
    test-boost-server.cpp
    test-coroutine-order.cpp
)

# study 下的每个 .cpp 编译为同名可执行文件，便于单独运行学习
foreach(dir lesson test)
    file(GLOB CC_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/study/${dir}/*.cpp)
    foreach(file ${CC_SOURCES})
        get_filename_component(name ${file} NAME)
        if(name IN_LIST CC_SKIPPED_SOURCES)
            message(STATUS "skip (boost not available): study/${dir}/${name}")
            continue()
        endif()
        get_filename_component(target ${file} NAME_WE)
        add_executable(${target} ${file})
        target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/study/common)
        target_link_libraries(${target} PRIVATE cppcoroutines Threads::Threads)
    endforeach()
endforeach()
