include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# 每个 test_*.cpp 编译为独立测试可执行文件，注册到 ctest
file(GLOB CC_TESTS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(file ${CC_TESTS})
    get_filename_component(target ${file} NAME_WE)
    add_executable(${target} ${file})
    target_link_libraries(${target} PRIVATE Catch2::Catch2WithMain cppcoroutines)
    add_test(NAME ${target} COMMAND ${target})
endforeach()
