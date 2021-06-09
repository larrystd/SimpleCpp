cmake_minimum_required(VERSION 3.7)
project(red_blue)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

set(SOURCE_FILES main.c barrier.c)
add_executable(main ${SOURCE_FILES})

target_link_libraries (main ${CMAKE_THREAD_LIBS_INIT})
