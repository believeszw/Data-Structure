//
// Created by believe on 2020/4/14.
//

#include "loop_queue.hpp"
#include "gtest/gtest.h"

class LoopQueueTest : public testing::Test {
protected:
  void SetUp() override {
    for (int kI = 0; kI < 10; ++kI) {
      loop_queue_.Enqueue(kI);
    }
  }
  void TearDown() override { loop_queue_.Clear(); }
  LoopQueue<int> loop_queue_;
};

TEST(LoopQueueTestNoF, IsEmpty) {
  LoopQueue<int> loop_queue(15);
  EXPECT_TRUE(loop_queue.IsEmpty());
}

TEST(LoopQueueTestNoF, EnqueAndDeque) {
  LoopQueue<int> loop_queue;
  loop_queue.Enqueue(1);
  loop_queue.Enqueue(2);
  loop_queue.Enqueue(3);
  EXPECT_EQ(1, loop_queue.Dequeue());
  EXPECT_EQ(2, loop_queue.Dequeue());
  EXPECT_EQ(3, loop_queue.Dequeue());
}

TEST_F(LoopQueueTest, GetSizeAndGetCapacity) {
  EXPECT_EQ(10, loop_queue_.GetSize());
  EXPECT_EQ(10, loop_queue_.GetCapacity());
  EXPECT_EQ(0, loop_queue_.GetFront());
}

TEST_F(LoopQueueTest, CopyConstructorTest) {
  LoopQueue<int> array_stack(loop_queue_);
  EXPECT_EQ(10, array_stack.GetSize());
  EXPECT_EQ(0, array_stack.GetFront());
}

TEST_F(LoopQueueTest, CopyAssignedTest) {
  LoopQueue<int> loop_queue;
  loop_queue = loop_queue_;
  EXPECT_EQ(10, loop_queue.GetSize());
  EXPECT_EQ(0, loop_queue.GetFront());
}

TEST_F(LoopQueueTest, MoveTest) {
  // 移动拷贝构造
  LoopQueue<int> loop_queue(std::move(loop_queue_));

  // 移动赋值传入本身 会报错
  //  loop_queue = std::move(loop_queue);
  //  EXPECT_EQ(10,loop_queue.GetSize());
  //  EXPECT_EQ(0,loop_queue.GetFront());

  LoopQueue<int> loop_queue1;
  // 移动赋值
  loop_queue1 = std::move(loop_queue);
  EXPECT_EQ(0, loop_queue_.GetSize());
  EXPECT_EQ(0, loop_queue.GetSize());
  EXPECT_EQ(10, loop_queue1.GetSize());
  EXPECT_EQ(0, loop_queue1.GetFront());
}

TEST_F(LoopQueueTest, OperatorTest) {
  //  std::cout << loop_queue_ << std::endl;
}