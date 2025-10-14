cmake_minimum_required(VERSION 4.0)
project(cpp_lab2_task10)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(cpp_lab2_task10 main.cpp
        utils.h
        utils.cpp
        custom_parallel.h
        performance_study.h
        performance_study.cpp)

target_link_libraries(cpp_lab2_task10 PRIVATE Threads::Threads)
