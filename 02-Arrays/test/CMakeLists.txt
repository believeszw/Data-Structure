project(ArraysTest)

#include_directories(${PROJECT_SOURCE_DIR}/../../include)
include_directories(${PROJECT_SOURCE_DIR}/../src)
#link_directories(${PROJECT_SOURCE_DIR}/../../gtest)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${COMPILE_PLAT})

SET(TEST_SRC array_test.cpp)

SET(TEST_LIB gtest gtest_main -lpthread)

add_executable(ArraysTest ${TEST_SRC})

target_link_libraries(ArraysTest ${TEST_LIB})
INSTALL(TARGETS ArraysTest DESTINATION ${EXECUTABLE_OUTPUT_PATH})

