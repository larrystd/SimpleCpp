cmake_minimum_required(VERSION 2.6)

project(http C CXX)

include_directories(/home/larry/programs/c++code/database)

add_library(mysqllib mysql_connection_sp.cc)
target_link_libraries(mysqllib mysqlcppconn)

add_executable(mysqlcpp mysql_test.cpp)
target_link_libraries(mysqlcpp mysqllib)