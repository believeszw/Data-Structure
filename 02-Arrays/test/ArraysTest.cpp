//
// Created by believe on 2019/9/18.

#include "gtest/gtest.h"
#include "MyArray.h"


class ArrayTest : public testing::Test {
 protected:
  void SetUp() override {
    Test::SetUp();
  }
  void TearDown() override {
    Test::TearDown();
  }
};

TEST_F(ArrayTest, Add) {
  MyArray my_array;
  my_array.add(0,1);
  EXPECT_EQ()
}