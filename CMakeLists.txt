cmake_minimum_required(VERSION 3.14)
project(Data_structure)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --coverage")

add_subdirectory(02-Arrays)
add_subdirectory(03-Stacks-and-Queues)
