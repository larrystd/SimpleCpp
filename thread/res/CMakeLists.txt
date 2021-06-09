cmake_minimum_required(VERSION 3.7)
project(red_blue)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

set(SOURCE_FILES red_blue.c barrier.c)
add_executable(red_blue ${SOURCE_FILES})

target_link_libraries (red_blue ${CMAKE_THREAD_LIBS_INIT})
