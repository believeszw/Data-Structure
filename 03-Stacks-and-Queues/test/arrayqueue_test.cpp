//
// Created by believe on 2020/1/22.
//

#include "array_queue.hpp"
#include "gtest/gtest.h"

class ArrayQueueTest : public testing::Test {
protected:
  void SetUp() override {
    for (int kI = 0; kI < 10; ++kI) {
      array_queue_.Enqueue(kI);
    }
  }
  void TearDown() override { array_queue_.Clear(); }
  ArrayQueue<int> array_queue_;
};

TEST(ArrayQueueTestNoF, IsEmpty) {
  ArrayQueue<int> array_queue(15);
  EXPECT_TRUE(array_queue.IsEmpty());
}

TEST(ArrayQueueTestNoF, EnqueAndDeque) {
  ArrayQueue<int> array_queue;
  array_queue.Enqueue(1);
  array_queue.Enqueue(2);
  array_queue.Enqueue(3);
  EXPECT_EQ(1, array_queue.Dequeue());
  EXPECT_EQ(2, array_queue.Dequeue());
  EXPECT_EQ(3, array_queue.Dequeue());
}

TEST_F(ArrayQueueTest, GetSizeAndGetCapacity) {
  EXPECT_EQ(10, array_queue_.GetSize());
  EXPECT_EQ(10, array_queue_.GetCapacity());
  EXPECT_EQ(0, array_queue_.GetFront());
}

TEST_F(ArrayQueueTest, CopyConstructorTest) {
  ArrayQueue<int> array_stack(array_queue_);
  EXPECT_EQ(10, array_stack.GetSize());
  EXPECT_EQ(0, array_stack.GetFront());
}

TEST_F(ArrayQueueTest, CopyAssignedTest) {
  ArrayQueue<int> array_queue;
  array_queue = array_queue_;
  EXPECT_EQ(10, array_queue.GetSize());
  EXPECT_EQ(0, array_queue.GetFront());
}

TEST_F(ArrayQueueTest, MoveTest) {
  // 移动拷贝构造
  ArrayQueue<int> array_queue(std::move(array_queue_));

  // 移动赋值传入本身 会报错
  //  array_queue = std::move(array_queue);
  //  EXPECT_EQ(10,array_queue.GetSize());
  //  EXPECT_EQ(0,array_queue.GetFront());

  ArrayQueue<int> array_queue1;
  // 移动赋值
  array_queue1 = std::move(array_queue);
  EXPECT_EQ(0, array_queue_.GetSize());
  EXPECT_EQ(0, array_queue.GetSize());
  EXPECT_EQ(10, array_queue1.GetSize());
  EXPECT_EQ(0, array_queue1.GetFront());
}

TEST_F(ArrayQueueTest, OperatorTest) { std::cout << array_queue_ << std::endl; }