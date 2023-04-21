//
// Created by believe on 2020/1/20.
//

#include "gtest/gtest.h"
#include "array_stack.hpp"

class ArrayStackTest : public testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      array_stack_.Push(i);
    }
  }
  void TearDown() override {
    array_stack_.Clear();
  }
  ArrayStack<int> array_stack_;
};

GTEST_API_ int main(int argc, char **argv)
{
  std::cout << "Run All Test ! " << std::endl;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ArrayStackTestNoF, IsEmpty) {
  ArrayStack<int> array_stack(10);
  EXPECT_TRUE(array_stack.IsEmpty());
}

TEST(ArrayStackTestNoF, PushAndPop) {
  ArrayStack<int> array_stack;
  array_stack.Push(1);
  array_stack.Push(2);
  array_stack.Push(3);
  EXPECT_EQ(3,array_stack.Pop());
  EXPECT_EQ(2,array_stack.Pop());
  EXPECT_EQ(1,array_stack.Pop());
}

TEST_F(ArrayStackTest, GetSizeAndGetCapacity) {
  EXPECT_EQ(10,array_stack_.GetSize());
  EXPECT_EQ(10,array_stack_.GetCapacity());
  EXPECT_EQ(9,array_stack_.Peek());
}

TEST_F(ArrayStackTest, CopyConstructorTest) {
  ArrayStack<int> array_stack(array_stack_);
  EXPECT_EQ(10,array_stack.GetSize());
  EXPECT_EQ(9,array_stack.Peek());
}

TEST_F(ArrayStackTest, CopyAssignedTest) {
  ArrayStack<int> array_stack;
  array_stack = array_stack_;
  EXPECT_EQ(10,array_stack.GetSize());
  EXPECT_EQ(9,array_stack.Peek());
}

TEST_F(ArrayStackTest, MoveTest) {
  // 移动拷贝构造
  ArrayStack<int> array_stack(std::move(array_stack_));

  // 移动赋值传入本身 会报错
//  array_stack = std::move(array_stack);
//  EXPECT_EQ(10,array_stack.GetSize());
//  EXPECT_EQ(9,array_stack.Peek());

  ArrayStack<int> array_stack1;
  // 移动赋值
  array_stack1 = std::move(array_stack);
  EXPECT_EQ(0,array_stack_.GetSize());
  EXPECT_EQ(0,array_stack.GetSize());
  EXPECT_EQ(10,array_stack1.GetSize());
  EXPECT_EQ(9,array_stack1.Peek());
}

TEST_F(ArrayStackTest, OperatorTest) {
  std::cout << array_stack_ << std::endl;
}