//
// Created by believe on 2023/4/20.
//

#include "gtest/gtest.h"
#include "iostream"
#include "thread"
#include "lock_free_ptr.hpp"


int main() {
//    std::cout << typeid(B).name() << std::endl;
    auto sp = std::make_shared<int> (4);
    int *ptr = new int[4];
    lf_atomic_shared_ptr<int> s(ptr);
    std::thread([&]{
        static int i = 0;
        auto begin = std::chrono::high_resolution_clock::now();
        while (1){
            s = std::make_shared<int>(i++);
            if(**s == 100000000){
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "branch mark " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() <<  std::endl;
                break;
            }
        }

    }).detach();
    std::thread([&]{
        int cnt = 0;
        while (1) {
            cnt += **s;
            if(**s == 100000000) break;
        }
    }).detach();
    while (1);
//    int * && p = new int(2);
//    std::cout << typeid(int * &&).name() << std::endl;
//    std::cout << typeid(const int * &).name() << std::endl;
//    int * fp = new int(4);
//    f(fp);
//    f("123");
//    std :: cout << (7&~(0x01)) << std::endl;
//    std::map<int,std::mutex> m;
//
//    m.emplace(std::piecewise_construct,
//              std::forward_as_tuple(0),
//            std::forward_as_tuple());
//    m[0].lock();
//    m[0].unlock();
//    //    auto pt = std::chrono::system_clock::now().time_since_epoch();
////    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(pt).count() << std::endl;
////    auto ptr = std::make_exception_ptr(std::system_error(errno,std::system_category()));
//    auto begin = std::chrono::steady_clock::now();
//
//    auto handle = dlopen("libttvideoeditor-c.dylib", RTLD_LAZY);
//
//    std::string str = "hello ,\"key\":123, world";
//    auto find_it = str.find("\"key\":", 0);
////    auto find_end = std::find_if(str.begin() + find_it,str.end(),[] (char ch){
////        return ch == ','|| ch =='\0' || ch=='}';
////    });
//    auto find_end = str.find_first_of(",}",find_it);
//    str.erase(find_it,find_end - find_it + 1 );
//    std::cout << str << std::endl;
//    auto end = std::chrono::steady_clock::now();
//
//
//   std::cout << std::abs(std::numeric_limits<int>::min()) << std::endl;
}

// 初始化
//class SharedPtrTest : public testing::Test {
// protected:
//  void SetUp() override {
//    for (int i = 0; i < 10; ++i) {
//      my_array_.AddLast(i);
//    }
//  }
//  void TearDown() override {
//    my_array_.Clear();
//  }
//  lf_atomic_shared_ptr<int> my_array_;
//};
//
//GTEST_API_ int main(int argc, char **argv)
//{
//    std::cout << "Run All Test ! " << std::endl;
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
//
//TEST(SharedPtrTestNoF, IsEmpty) {
//  MyArray<int> my_array(10);
//  EXPECT_TRUE(my_array.IsEmpty());
//}
//
//TEST(SharedPtrTestNoF, AddAndGet) {
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
//TEST_F(SharedPtrTest, GetSizeAndGetCapacity) {
//    int a = new int[100];
//    a[1] = 1;
//  EXPECT_EQ(10,my_array_.GetCapacity());
//  EXPECT_EQ(10,my_array_.GetSize());
//}
//
//TEST_F(SharedPtrTest, Remove) {
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
//TEST_F(SharedPtrTest, Set) {
//  my_array_.Set(0,11);
//  EXPECT_EQ(11,my_array_.GetFirst());
//}
//
//TEST_F(SharedPtrTest, FindAndContain) {
//  EXPECT_EQ(0,my_array_.Find(0));
//  EXPECT_TRUE(my_array_.Contain(1));
//  EXPECT_FALSE(my_array_.Contain(111));
//}
//
//TEST_F(SharedPtrTest, Resize) {
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
//TEST_F(SharedPtrTest, SquareBracketsTest) {
//  EXPECT_EQ(0,my_array_[0]);
//  EXPECT_EQ(1,my_array_[1]);
//}
//
//// 拷贝构造测试
//TEST_F(SharedPtrTest, CopyConstructorTest) {
//  MyArray<int> my_array(my_array_);
//  EXPECT_EQ(10,my_array.GetSize());
//  EXPECT_EQ(9,my_array.Get(9));
//}
//
//// 赋值拷贝测试
//TEST_F(SharedPtrTest, CopyAssignedTest) {
//  MyArray<int> my_array;
//  my_array = my_array_;
//  EXPECT_EQ(10,my_array.GetSize());
//  EXPECT_EQ(9,my_array.Get(9));
//}
//
//// 移动构造和移动赋值测试
//TEST_F(SharedPtrTest, MoveTest) {
//  // 移动拷贝构造
//  MyArray<int> my_array(std::move(my_array_));
//
//  // 移动赋值传入本身 会报错
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
//TEST_F(SharedPtrTest, OperatorTest) {
//  std::cout << my_array_ << std::endl;
//}
//
//// 100% 覆盖率，少数情况
//TEST_F(SharedPtrTest, AdditionTest) {
//  EXPECT_THROW(MyArray<int> my_array(-1), std::invalid_argument);
//  EXPECT_THROW(my_array_[-1], std::invalid_argument);
//  EXPECT_THROW(my_array_.Add(-1, -1), std::invalid_argument);
//  EXPECT_THROW(my_array_.Get(-1), std::invalid_argument);
//  EXPECT_THROW(my_array_.Set(-1, -1), std::invalid_argument);
//  EXPECT_THROW(my_array_.Remove(-1), std::invalid_argument);
//}
