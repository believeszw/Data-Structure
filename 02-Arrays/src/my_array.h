//
// Created by believe on 2019/9/18.
//

#ifndef DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_
#define DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_

#include <iostream>
#include <utility>
#include <stdexcept>
#include <cassert>

template<typename T>
class MyArray {
 private:
  int size_{0};
  int capacity_{0};
  T *data_{nullptr};

 public:
  MyArray();                                         // 无参构造函数
  explicit MyArray(int capacity);                    // 构造函数，传入容量 capacity
  ~MyArray();                                        // *析构函数阻止隐式移动构造函数
  MyArray(const MyArray<T> &arr);                    // 拷贝构造
  MyArray(MyArray<T> &&arr) noexcept;                // 移动构造函数
  MyArray<T> &operator=(const MyArray<T> &arr);      // 重载赋值操作符
  MyArray<T> &operator=(MyArray<T> &&arr) noexcept;  // 重载移动赋值操作符
  T &operator[](int index);                          // 重载 [] 操作赋

  // 友元函数实现 重载输出 << 操作符
  friend std::ostream &operator<<(std::ostream &out, MyArray<T> &obj) {
    out << "MyArray size = " << obj.size_ << ", Capacity = " << obj.capacity_ << std::endl;
    out << "MyArray: [";
    for (int i = 0; i < obj.size_; ++i) {
      out << obj.data_[i];
      if (i != obj.size_ - 1)
        out << ", ";
    }
    out << "] ";

    return out;
  }

  int  GetSize() const;            // 获取数组元素个数
  int  GetCapacity() const;        // 获取数组容量
  bool IsFull() const;             // 判断数组是否已满
  bool IsEmpty() const;            // 判断数组是否为空
  void Add(int index, T t);        // 在指定位置插入元素 t
  void AddFirst(T t);              // 头部添加元素
  void AddLast(T t);               // 尾部添加元素
  void Set(int index, T t);        // 将指定位置元素设为 t
  T    Get(int index) const;       // 查看 index 位置的元素
  T    GetFirst() const;           // 获取第一个元素
  T    GetLast() const;            // 获取最后一个元素
  T    Remove(int index);          // 删除指定位置元素
  T    RemoveFirst();              // 删除第一个元素
  T    RemoveLast();               // 删除最后一个元素
  void RemoveElement(T t);         // 删除元素 t
  void Clear();                    // 清空数组
  int  Find(T t) const;            // 查找元素 t 的下标
  bool Contain(T t) const;         // 判断是否包含元素 t
  void Resize(int new_capacity);   // 重新分配空间
};

template<typename T>
MyArray<T>::MyArray() {
  capacity_ = 10;
  data_     = new T[capacity_];
  std::cout << "调用 MyArray() 构造." << std::endl;
}

template<typename T>
MyArray<T>::MyArray(int capacity) {
  if (capacity <= 0) {
    std::cout << "MyArray(int) error. Capacity is illegal." << std::endl;
    throw std::invalid_argument("MyArray(int) error. Capacity is illegal.");
  }
  capacity_ = capacity;
  data_     = new T[capacity_];
  std::cout << "调用 MyArray(int capacity) 构造." << std::endl;
}

template<typename T>
MyArray<T>::~MyArray() {
  if (nullptr != data_) {
    delete[] data_;
    data_ = nullptr;
  }
  size_     = 0;
  capacity_ = 0;
  std::cout << "调用 ~MyArray() 析构." << std::endl;
}

template<typename T>
MyArray<T>::MyArray(const MyArray<T> &arr) {
  this->size_     = arr.size_;
  this->capacity_ = arr.capacity_;
  this->data_     = new T[capacity_];
  for (int i = 0; i < size_; ++i) {
    this->data_[i] = arr.data_[i];
  }
  std::cout << "调用  MyArray(const MyArray &arr) 拷贝构造" << std::endl;
}

template<typename T>
MyArray<T>::MyArray(MyArray<T> &&arr) noexcept {
  assert(this != &arr);
  capacity_ = std::exchange(arr.capacity_, 0);
  size_     = std::exchange(arr.size_, 0);       // 非类类型成员的显式移动 // 类类型成员的显式移动使用 std::move
  data_     = std::exchange(arr.data_, nullptr);
  std::cout << "调用  MyArray(const MyArray &&arr) 移动构造函数" << std::endl;
}

template<typename T>
MyArray<T> &MyArray<T>::operator=(const MyArray<T> &arr) {
  assert(this != &arr);
  if (this->data_ != nullptr) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
  // 分配内存
  this->size_     = arr.size_;
  this->capacity_ = arr.capacity_;
  this->data_     = new T[capacity_];
  // 拷贝数据
  for (int i = 0; i < size_; i++) {
    // 如果是自定义的复杂数据类型，必须对 = 运算赋进行重载,  operator=
    this->data_[i] = arr.data_[i];
  }

  std::cout << "调用 MyArray = 赋值操作 " << std::endl;
  return *this;
}

template<typename T>
MyArray<T> &MyArray<T>::operator=(MyArray<T> &&arr) noexcept {
  assert(this != &arr);
  if (this->data_ != nullptr) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
  // 分配内存
  this->size_ = std::exchange(arr.size_, 0);
  this->capacity_ = std::exchange(arr.capacity_, 0);
  this->data_ = std::exchange(arr.data_, nullptr);
  std::cout << "调用 MyArray = 移动赋值操作 " << std::endl;
  return *this;
}

template<typename T>
T &MyArray<T>::operator[](int index) {
  if (index < 0 || index >= size_) {
    std::cout << "[] fail. Index is illegal." << std::endl;
    throw std::invalid_argument("[] fail. Index is illegal.");
  }
  std::cout << "MyArray [] 调用" << std::endl;
  return this->data_[index];
}

template<typename T>
bool MyArray<T>::IsFull() const {
  return size_ == capacity_;
}

template<typename T>
bool MyArray<T>::IsEmpty() const {
  return size_ == 0;
}

template<typename T>
void MyArray<T>::Add(int index, T t) {
  if (index < -1 || index > size_) {
    std::cout << "Add fail. Index is illegal." << std::endl;
    throw std::invalid_argument("Add fail. Index is illegal.");
  }
  if (IsFull()) {
    Resize(capacity_ * 2);
  }
  for (int i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = t;
  size_++;
}

template<typename T>
void MyArray<T>::AddFirst(T t) {
  Add(0, t);
}

template<typename T>
void MyArray<T>::AddLast(T t) {
  Add(size_, t);
}

template<typename T>
void MyArray<T>::Set(int index, T t) {
  if (index < 0 || index >= size_) {
    std::cout << "Set Fail. Index is illegal." << std::endl;
    throw std::invalid_argument("Set fail. Index is illegal.");
  }
  data_[index] = t;
}

template<typename T>
T MyArray<T>::Get(int index) const {
  if (index < -1 || index >= size_) {
    std::cout << "Get fail. Index is illegal." << std::endl;
    throw std::invalid_argument("Get fail. Index is illegal.");
  }

  return data_[index];
}

template<typename T>
T MyArray<T>::GetFirst() const {
  return Get(0);
}

template<typename T>
T MyArray<T>::GetLast() const {
  return Get(size_ - 1);
}

template<typename T>
int MyArray<T>::GetSize() const {
  return size_;
}

template<typename T>
int MyArray<T>::GetCapacity() const {
  return capacity_;
}

template<typename T>
T MyArray<T>::Remove(int index) {
  if (index < 0 || index >= size_) {
    std::cout << "Remove fail. Index is illegal." << std::endl;
    throw std::invalid_argument("Remove fail. Index is illegal.");
  }
  if (size_ <= capacity_ / 4 && capacity_ / 2 != 0) {
    Resize(capacity_ / 2);
  }

  T ret = data_[index];
  for (int i = index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }
  size_--;
  return ret;
}

template<typename T>
T MyArray<T>::RemoveFirst() {
  return Remove(0);
}

template<typename T>
T MyArray<T>::RemoveLast() {
  return Remove(size_ - 1);
}

template<typename T>
void MyArray<T>::RemoveElement(T t) {
  int index = Find(t);
  index != -1 && Remove(index);
}

template<typename T>
void MyArray<T>::Clear() {
  size_ = 0;
}

template<typename T>
int MyArray<T>::Find(T t) const {
  for (int i = 0; i < size_; ++i) {
    if (data_[i] == t) {
      return i;
    }
  }
  return -1;
}

template<typename T>
bool MyArray<T>::Contain(T t) const {
  return Find(t) != -1;
}

template<typename T>
void MyArray<T>::Resize(int new_capacity) {
  assert(new_capacity > 0);
  T *new_data = new T[new_capacity];
  for (int i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
  std::cout << "Resize Capacity = " << new_capacity << std::endl;
}

#endif // DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_
