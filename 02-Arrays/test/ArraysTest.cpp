//
// Created by believe on 2019/9/18.

#include "gtest/gtest.h"
#include "MyArray.h"

// 初始化
class ArrayTest : public testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      my_array_.AddLast(i);
    }
  }
  void TearDown() override {
    my_array_.Clear();
  }
  MyArray<int> my_array_;
};

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Run All Test ! " << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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

TEST_F(ArrayTest, GetSizeAndGetCapacity) {
  EXPECT_EQ(10,my_array_.GetCapacity());
  EXPECT_EQ(10,my_array_.GetSize());
}

TEST_F(ArrayTest, Remove) {
  EXPECT_EQ(10,my_array_.GetCapacity());
  EXPECT_EQ(10,my_array_.GetSize());
  EXPECT_EQ(1,my_array_.Remove(1));
  EXPECT_EQ(0,my_array_.RemoveFirst());
  EXPECT_EQ(9,my_array_.RemoveLast());
  EXPECT_EQ(7,my_array_.GetSize());
  my_array_.RemoveElement(2);
  EXPECT_EQ(6,my_array_.GetSize());
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

// [] 测试
TEST_F(ArrayTest, SquareBracketsTest) {
  EXPECT_EQ(0,my_array_[0]);
  EXPECT_EQ(1,my_array_[1]);
}

// 拷贝构造测试
TEST_F(ArrayTest, CopyConstructorTest) {
  MyArray<int> my_array(my_array_);
  EXPECT_EQ(10,my_array.GetSize());
  EXPECT_EQ(9,my_array.Get(9));
}

// 赋值拷贝测试
TEST_F(ArrayTest, CopyAssignedTest) {
  MyArray<int> my_array;
  my_array = my_array_;
  EXPECT_EQ(10,my_array.GetSize());
  EXPECT_EQ(9,my_array.Get(9));
}

// 移动构造和移动赋值测试
TEST_F(ArrayTest, MoveTest) {
  // 移动拷贝构造
  MyArray<int> my_array(std::move(my_array_));

  // 移动赋值传入本身 会报错
//  my_array = std::move(my_array);
//  EXPECT_EQ(10,my_array.GetSize());
//  EXPECT_EQ(9,my_array.Get(9));

  MyArray<int> my_array1;
  // 移动赋值
  my_array1 = std::move(my_array);
  EXPECT_EQ(10,my_array1.GetSize());
  EXPECT_EQ(0,my_array.GetSize());
  EXPECT_EQ(0,my_array_.GetSize());
  EXPECT_EQ(5,my_array1.Get(5));
}

// 测试 << 重载
TEST_F(ArrayTest, OperatorTest) {
  std::cout << my_array_ << std::endl;
}