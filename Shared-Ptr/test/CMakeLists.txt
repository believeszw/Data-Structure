project(SharedPtr)

#include_directories(${PROJECT_SOURCE_DIR}/../../include)
include_directories(${PROJECT_SOURCE_DIR}/../src)
#link_directories(${PROJECT_SOURCE_DIR}/../../gtest)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${COMPILE_PLAT})

SET(TEST_SRC shared_ptr_test.cpp)

SET(TEST_LIB gtest gtest_main -lpthread)

add_executable(SharedPtr ${TEST_SRC})

target_link_libraries(SharedPtr ${TEST_LIB})
INSTALL(TARGETS SharedPtr DESTINATION ${EXECUTABLE_OUTPUT_PATH})

