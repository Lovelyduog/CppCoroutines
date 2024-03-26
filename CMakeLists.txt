cmake_minimum_required(VERSION 3.18)
project(CppCoroutines)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

# 查询系统中的boost库
# link_directories(${PROJECT_SOURCE_DIR}/external/3rd/lib)
# link_directories(${PROJECT_SOURCE_DIR}/external/lib)
include_directories(/home/huangruiguo/workspace/project_zero/server/external/include)

# list all c files in current dir recursively.
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
    target_link_libraries(${name} PRIVATE pthread)
    # target_link_libraries(${name} Boost::boost)
    link_directories(/home/huangruiguo/workspace/project_zero/server/external/3rd/lib)
    link_directories(/home/huangruiguo/workspace/project_zero/server/external/lib)
endforeach()