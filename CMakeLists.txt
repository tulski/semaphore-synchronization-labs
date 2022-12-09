cmake_minimum_required(VERSION 3.23)
project(kso_lab_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(full_test full_test.cpp queue.h buffer.h actors.h color_log.h repository.h)
add_executable(queue_test queue_test.cpp queue.h buffer.h)
add_executable(simple_test simple_test.cpp queue.h buffer.h actors.h color_log.h repository.h)