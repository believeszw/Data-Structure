//
// Created by believe on 2020/1/22.
//

#include "gtest/gtest.h"
#include "array_queue.h"

class ArrayQueueTest : public testing::Test {
 protected:
  void SetUp() override {
    for (int kI = 0; kI < 10; ++kI) {
      array_queue_.Enqueue(kI);
    }
  }
  void TearDown() override {
    array_queue_.Clear();
  }
  ArrayQueue<int> array_queue_;
};

TEST(ArrayQueueTestNoF,NOF){
  ArrayQueue<int> array_queue(15);
  EXPECT_TRUE(array_queue.IsEmpty());
}

TEST_F(ArrayQueueTest, GetSizeAndGetCapacity) {
  EXPECT_EQ(10,array_queue_.GetSize());
  EXPECT_EQ(10,array_queue_.GetCapacity());
  EXPECT_EQ(0,array_queue_.GetFront());
}

TEST_F(ArrayQueueTest, CopyConstructorTest) {
  ArrayQueue<int> array_stack(array_queue_);
  EXPECT_EQ(10,array_stack.GetSize());
  EXPECT_EQ(0,array_stack.GetFront());
}

//TEST_F(ArrayQueueTest, CopyAssignedTest) {
//  ArrayStack<int> array_stack;
//  array_stack = array_stack_;
//  EXPECT_EQ(10,array_stack.GetSize());
//  EXPECT_EQ(9,array_stack.Peek());
//}
//
//TEST_F(ArrayQueueTest, MoveTest) {
//  // 移动拷贝构造
//  ArrayStack<int> array_stack(std::move(array_stack_));
//
//  // 移动赋值传入本身 会报错
////  array_stack = std::move(array_stack);
////  EXPECT_EQ(10,array_stack.GetSize());
////  EXPECT_EQ(9,array_stack.Peek());
//
//  ArrayStack<int> array_stack1;
//  // 移动赋值
//  array_stack1 = std::move(array_stack);
//  EXPECT_EQ(0,array_stack_.GetSize());
//  EXPECT_EQ(0,array_stack.GetSize());
//  EXPECT_EQ(10,array_stack1.GetSize());
//  EXPECT_EQ(9,array_stack1.Peek());
//}
//
//TEST_F(ArrayQueueTest, OperatorTest) {
//  std::cout << array_stack_ << std::endl;
//}