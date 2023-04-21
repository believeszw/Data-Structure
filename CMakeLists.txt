cmake_minimum_required(VERSION 3.14)
project(Data_structure)

set(CMAKE_CXX_STANDARD 20)

# googletest
set(GOOGLETEST_VERSION 1.10.0)
add_subdirectory(
        googletest/googletest
)
include_directories(
        googletest/googletest/include
)
# end

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    MESSAGE("This is Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    MESSAGE("This is Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# -g 调试信息
# -Wall 开启所有警告
# -Werror 警告视为错误
# -fsanitize=address
# Out-of-bounds accesses to heap, stack and globals
# Use-after-free
# Use-after-return (runtime flag ASAN_OPTIONS=detect_stack_use_after_return=1)
# Use-after-scope (clang flag -fsanitize-address-use-after-scope)
# Double-free, invalid free
# Memory leaks (experimental)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -fno-omit-frame-pointer -fno-optimize-sibling-calls \
-fsanitize=undefined -fPIE") # -fsanitize=memory -fsanitize-memory-track-origins -pie

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread") # 检查数据竞争
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory") # access uninited

# -fno-optimize-sibling-calls 尾递归消除
# -fno-omit-frame-pointer : 保留函数调用的帧信息，以便分析函数调用关系
# -fsanitize=undefined : 未定义行为检测
# -fsanitize=leak 开启后，可以出界更详细的错误信息

# --coverage 用于统计测试覆盖率
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

#set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化

add_subdirectory(02-Arrays)
add_subdirectory(03-Stacks-and-Queues)
add_subdirectory(Shared-Ptr)
