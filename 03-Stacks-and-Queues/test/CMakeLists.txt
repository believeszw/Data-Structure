project(StackQueues)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
include_directories(${PROJECT_SOURCE_DIR}/../src)
include_directories(${PROJECT_SOURCE_DIR}/../../02-Arrays/src)
link_directories(${PROJECT_SOURCE_DIR}/../../gtest)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${COMPILE_PLAT})

SET(TEST_SRC arraystack_test.cpp valid_parentheses.cpp arrayqueue_test.cpp)

SET(TEST_LIB gtest gtest_main -lpthread)

add_executable(StackQueuesTest ${TEST_SRC})

target_link_libraries(StackQueuesTest ${TEST_LIB})
INSTALL(TARGETS StackQueuesTest DESTINATION ${EXECUTABLE_OUTPUT_PATH})

