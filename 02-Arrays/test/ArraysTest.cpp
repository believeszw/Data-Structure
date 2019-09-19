//
// Created by believe on 2019/9/18.

#include "gtest/gtest.h"
#include "MyArray.h"


class ArrayTest : public testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      my_array_.AddLast(i);
    }
  }
  void TearDown() override {
  }
  MyArray<int> my_array_;
};

TEST(ArrayTestNoF, IsEmpty) {
  MyArray<int> my_array(10);
  EXPECT_TRUE(my_array.IsEmpty());
}

TEST(ArrayTestNoF, AddAndGet) {
  MyArray<int> my_array;
  my_array.Add(0,1);
  my_array.Add(1,2);
  my_array.Add(2,3);
  EXPECT_EQ(1,my_array.Get(0));
  EXPECT_EQ(2,my_array.Get(1));
  EXPECT_EQ(3,my_array.Get(2));
  my_array.AddFirst(4);
  EXPECT_EQ(4,my_array.Get(0));
  EXPECT_EQ(4,my_array.GetFirst());
  my_array.AddLast(5);
  EXPECT_EQ(5,my_array.Get(4));
  EXPECT_EQ(5,my_array.GetLast());
}

TEST_F(ArrayTest, Remove) {
  EXPECT_EQ(10,my_array_.GetCapacity());
  EXPECT_EQ(10,my_array_.GetSize());
  EXPECT_EQ(1,my_array_.Remove(1));
  EXPECT_EQ(0,my_array_.RemoveFirst());
  EXPECT_EQ(9,my_array_.RemoveLast());
  EXPECT_EQ(7,my_array_.GetSize());
}

TEST_F(ArrayTest, Set) {
  my_array_.Set(0,11);
  EXPECT_EQ(11,my_array_.GetFirst());
}

TEST_F(ArrayTest, FindAndContain) {
  EXPECT_EQ(0,my_array_.Find(0));
  EXPECT_TRUE(my_array_.Contain(1));
  EXPECT_FALSE(my_array_.Contain(111));
}

TEST_F(ArrayTest, Resize) {
  EXPECT_EQ(10,my_array_.GetSize());
  EXPECT_EQ(10,my_array_.GetCapacity());
  my_array_.AddLast(10);
  EXPECT_EQ(11,my_array_.GetSize());
  EXPECT_EQ(20,my_array_.GetCapacity());
  for (int j = 0; j < 6; ++j) {
    my_array_.RemoveLast();
  }
  EXPECT_EQ(5,my_array_.GetSize());
  EXPECT_EQ(20,my_array_.GetCapacity());
  my_array_.RemoveLast();
  EXPECT_EQ(4,my_array_.GetSize());
  EXPECT_EQ(10,my_array_.GetCapacity());
}

TEST_F(ArrayTest, SquareBracketsTest) {
  EXPECT_EQ(0,my_array_[0]);
  EXPECT_EQ(1,my_array_[1]);
}

TEST_F(ArrayTest, CopyTest) {
  MyArray<int> my_array(my_array_);
  EXPECT_EQ(10,my_array.GetSize());
  EXPECT_EQ(9,my_array.Get(9));
}

TEST_F(ArrayTest, EqualSignTest) {
  MyArray<int> my_array;
  my_array = my_array_;
  EXPECT_EQ(10,my_array.GetSize());
  EXPECT_EQ(9,my_array.Get(9));
}

TEST_F(ArrayTest, MoveTest) {
  MyArray<int> my_array(std::move(my_array_));
  EXPECT_EQ(10,my_array.GetSize());
  EXPECT_EQ(9,my_array.Get(9));
}

TEST_F(ArrayTest, OperatorTest) {
  std::cout << my_array_ << std::endl;
}