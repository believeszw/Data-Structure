cmake_minimum_required(VERSION 3.14)
project(Data_structure)

set(CMAKE_CXX_STANDARD 14)

# --coverage 用于统计测试覆盖率
# -fsanitize=address
# Out-of-bounds accesses to heap, stack and globals
# Use-after-free
# Use-after-return (runtime flag ASAN_OPTIONS=detect_stack_use_after_return=1)
# Use-after-scope (clang flag -fsanitize-address-use-after-scope)
# Double-free, invalid free
# Memory leaks (experimental)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --coverage -fsanitize=address")

add_subdirectory(02-Arrays)
add_subdirectory(03-Stacks-and-Queues)
