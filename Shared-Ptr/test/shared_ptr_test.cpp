//
// Created by believe on 2023/4/20.
//

#include "iostream"
#include "lock_free_ptr.hpp"
#include "spin_lock_ptr.hpp"
#include "thread"
#include "gtest/gtest.h"

#include <atomic>
#include <chrono>
#include <vector>

using namespace std::chrono_literals;

struct Data {
  int value;
  char buffer[1024];

  Data() {
    value = 0;
    for (int i = 0; i < 1024; ++i) {
      buffer[i] = 'a';
    }
  }

  Data(int value) : value(value) {
    for (int i = 0; i < 1024; ++i) {
      buffer[i] = 'a' + (i % 26);
    }
  }
};

std::atomic<bool> stop(false);

template <typename SmartPtr> void WriterThread(SmartPtr &global_ptr) {
  while (!stop) {
    global_ptr = SmartPtr(new Data(123));
    std::this_thread::sleep_for(10us);
  }
}

template <typename SmartPtr>
void ReaderThread(SmartPtr &global_ptr, std::atomic<int> &count) {
  while (!stop) {
    SmartPtr local_ptr = global_ptr;
    if (local_ptr) {
      ++count;
    }
  }
}

template <typename SmartPtr> void Test(const std::string &name) {
  SmartPtr global_ptr;
  std::atomic<int> count(0);
  std::vector<std::thread> threads;
  threads.push_back(std::thread(WriterThread<SmartPtr>, std::ref(global_ptr)));
  threads.push_back(std::thread(WriterThread<SmartPtr>, std::ref(global_ptr)));
  threads.push_back(std::thread(ReaderThread<SmartPtr>, std::ref(global_ptr),
                                std::ref(count)));
  threads.push_back(std::thread(ReaderThread<SmartPtr>, std::ref(global_ptr),
                                std::ref(count)));

  std::this_thread::sleep_for(1s);
  stop = true;

  for (auto &t : threads) {
    t.join();
  }

  std::cout << name << " read count: " << count << std::endl;
}

// int main() {
//     Test<LockFreeSharedPtr<Data>>("LockFreeSharedPtr");
////    Test<lf_atomic_shared_ptr<Data>>("OtherSmartPtr");
//
//    return 0;
//}

// 初始化
class SharedPtrTest : public testing::Test {
protected:
  void SetUp() override {
    for (int i = 0; i < 10; ++i) {
      //      my_array_.AddLast(i);
    }
  }
  void TearDown() override {
    //    my_array_.Clear();
  }
  //  lf_atomic_shared_ptr<int> my_array_;
};

GTEST_API_ int main(int argc, char **argv) {
  std::cout << "SharedPtr Run All Test ! " << std::endl;
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(SharedPtrTestNoF, IsEmpty) {
  std::cout << "SharedPtrTestNoF " << std::endl;
  //  MyArray<int> my_array(10);
  EXPECT_TRUE(true);
}
//
// TEST(SharedPtrTestNoF, AddAndGet) {
////  int * tmp = new int[10];
////  tmp[0] = 1;
//  MyArray<int> my_array;
//  my_array.Add(0,1);
//  my_array.Add(1,2);
//  my_array.Add(2,3);
//  EXPECT_EQ(1,my_array.Get(0));
//  EXPECT_EQ(2,my_array.Get(1));
//  EXPECT_EQ(3,my_array.Get(2));
//  my_array.AddFirst(4);
//  EXPECT_EQ(4,my_array.Get(0));
//  EXPECT_EQ(4,my_array.GetFirst());
//  my_array.AddLast(5);
//  EXPECT_EQ(5,my_array.Get(4));
//  EXPECT_EQ(5,my_array.GetLast());
//}
//
// TEST_F(SharedPtrTest, GetSizeAndGetCapacity) {
//    int a = new int[100];
//    a[1] = 1;
//  EXPECT_EQ(10,my_array_.GetCapacity());
//  EXPECT_EQ(10,my_array_.GetSize());
//}
//
// TEST_F(SharedPtrTest, Remove) {
//  EXPECT_EQ(10,my_array_.GetCapacity());
//  EXPECT_EQ(10,my_array_.GetSize());
//  EXPECT_EQ(1,my_array_.Remove(1));
//  EXPECT_EQ(0,my_array_.RemoveFirst());
//  EXPECT_EQ(9,my_array_.RemoveLast());
//  EXPECT_EQ(7,my_array_.GetSize());
//  my_array_.RemoveElement(2);
//  EXPECT_EQ(6,my_array_.GetSize());
//}
//
// TEST_F(SharedPtrTest, Set) {
//  my_array_.Set(0,11);
//  EXPECT_EQ(11,my_array_.GetFirst());
//}
//
// TEST_F(SharedPtrTest, FindAndContain) {
//  EXPECT_EQ(0,my_array_.Find(0));
//  EXPECT_TRUE(my_array_.Contain(1));
//  EXPECT_FALSE(my_array_.Contain(111));
//}
//
// TEST_F(SharedPtrTest, Resize) {
//  EXPECT_EQ(10,my_array_.GetSize());
//  EXPECT_EQ(10,my_array_.GetCapacity());
//  my_array_.AddLast(10);
//  EXPECT_EQ(11,my_array_.GetSize());
//  EXPECT_EQ(20,my_array_.GetCapacity());
//  for (int j = 0; j < 6; ++j) {
//    my_array_.RemoveLast();
//  }
//  EXPECT_EQ(5,my_array_.GetSize());
//  EXPECT_EQ(20,my_array_.GetCapacity());
//  my_array_.RemoveLast();
//  EXPECT_EQ(4,my_array_.GetSize());
//  EXPECT_EQ(10,my_array_.GetCapacity());
//}
//
//// [] 测试
// TEST_F(SharedPtrTest, SquareBracketsTest) {
//   EXPECT_EQ(0,my_array_[0]);
//   EXPECT_EQ(1,my_array_[1]);
// }
//
//// 拷贝构造测试
// TEST_F(SharedPtrTest, CopyConstructorTest) {
//   MyArray<int> my_array(my_array_);
//   EXPECT_EQ(10,my_array.GetSize());
//   EXPECT_EQ(9,my_array.Get(9));
// }
//
//// 赋值拷贝测试
// TEST_F(SharedPtrTest, CopyAssignedTest) {
//   MyArray<int> my_array;
//   my_array = my_array_;
//   EXPECT_EQ(10,my_array.GetSize());
//   EXPECT_EQ(9,my_array.Get(9));
// }
//
//// 移动构造和移动赋值测试
// TEST_F(SharedPtrTest, MoveTest) {
//   // 移动拷贝构造
//   MyArray<int> my_array(std::move(my_array_));
//
//   // 移动赋值传入本身 会报错
////  my_array = std::move(my_array);
////  EXPECT_EQ(10,my_array.GetSize());
////  EXPECT_EQ(9,my_array.Get(9));
//
//  MyArray<int> my_array1;
//  // 移动赋值
//  my_array1 = std::move(my_array);
//  EXPECT_EQ(10,my_array1.GetSize());
//  EXPECT_EQ(0,my_array.GetSize());
//  EXPECT_EQ(0,my_array_.GetSize());
//  EXPECT_EQ(5,my_array1.Get(5));
//}
//
//// 测试 << 重载
// TEST_F(SharedPtrTest, OperatorTest) {
//   std::cout << my_array_ << std::endl;
// }
//
//// 100% 覆盖率，少数情况
// TEST_F(SharedPtrTest, AdditionTest) {
//   EXPECT_THROW(MyArray<int> my_array(-1), std::invalid_argument);
//   EXPECT_THROW(my_array_[-1], std::invalid_argument);
//   EXPECT_THROW(my_array_.Add(-1, -1), std::invalid_argument);
//   EXPECT_THROW(my_array_.Get(-1), std::invalid_argument);
//   EXPECT_THROW(my_array_.Set(-1, -1), std::invalid_argument);
//   EXPECT_THROW(my_array_.Remove(-1), std::invalid_argument);
// }
