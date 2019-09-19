//
// Created by believe on 2019/9/18.
//

#ifndef DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_
#define DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_

template<typename T>
class MyArray {
 private:
  int size_;
  int capacity_;
  T* data_{nullptr};

 public:
  MyArray();                                   // 无参构造函数
  explicit MyArray(int capacity);              // 构造函数，传入容量 capacity
  ~MyArray();                                  // *析构函数阻止隐式移动构造函数
  MyArray(const MyArray &arr);                 // 拷贝构造
  MyArray(MyArray &&arr) noexcept;             // 移动构造函数
  MyArray &operator=(const MyArray& arr);      // 重载赋值操作符
  MyArray &operator=(MyArray&& arr) noexcept;  // 重载移动赋值操作符
  T &operator[](int index);                    // 重载[]操作赋

  //友元函数实现 重载输出 << 操作符
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

  bool IsFull() const;
  bool IsEmpty() const;
  void Add(int index, T t);
  void AddFirst(T t);
  void AddLast(T t);
  void Set(int index, T t);
  T Get(int index) const;
  T GetFirst() const;
  T GetLast() const;
  int GetSize() const;
  int GetCapacity() const;
  T Remove(int index);
  T RemoveFirst();
  T RemoveLast();
  void RemoveElement(T t);
  int Find(T t) const;
  bool Contain(T t) const;
  void Resize(int new_capacity);
};

template<typename T>
MyArray<T>::MyArray() {
  size_     = 0;
  capacity_ = 10;
  data_     = new T[capacity_];
  std::cout << "调用 MyArray() 构造." << std::endl;
}

template<typename T>
MyArray<T>::MyArray(int capacity) {
  if (capacity <= 0){
    std::cout << "MyArray(int) error. Capacity is illegal." << std::endl;
    throw "MyArray(int) error. Capacity is illegal.";
  }
  size_     = 0;
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
MyArray<T>::MyArray(const MyArray &arr) {
  this->size_     = arr.size_;
  this->capacity_ = arr.capacity_;
  this->data_     = new T[capacity_];
  for (int i = 0; i < size_; ++i) {
    this->data_[i] = arr.data_[i];
  }
  std::cout << "调用  MyArray(const MyArray &arr) 拷贝构造" << std::endl;
}

template<typename T>
MyArray<T>::MyArray(MyArray &&arr) noexcept {
  capacity_ = std::exchange(arr.capacity_, 0);
  size_ = std::exchange(arr.size_, 0);    // 非类类型成员的显式移动
  data_ = std::move(arr.data_);           // 类类型成员的显式移动
  arr.data_ = nullptr;
  std::cout << "调用  MyArray(const MyArray &&arr) 移动构造函数" << std::endl;
}

template<typename T>
MyArray<T> &MyArray<T>::operator=(const MyArray<T>& arr) {
  if (this->data_ != nullptr) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
  //分配内存
  this->size_ = arr.size_;
  this->capacity_ = arr.capacity_;
  this->data_ = new T[capacity_];
  //拷贝数据
  for (int i = 0; i < size_; i++) {
    //如果是自定义的复杂数据类型，必须对 = 运算赋进行重载,  operator=
    this->data_[i] = arr.data_[i];
  }

  std::cout << "调用 = 赋值操作 " << std::endl;
  return *this;
}

template<typename T>
MyArray<T> &MyArray<T>::operator=(MyArray<T> &&arr) noexcept {
  if (this == &arr) {
    std::cout << "调用 = 移动赋值操作 " << std::endl;
    return *this;
  }
  if (this->data_ != nullptr) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
  //分配内存
  this->size_ = std::exchange(arr.size_, 0);
  this->capacity_ = std::exchange(arr.capacity_, 0);
  this->data_ = new T[capacity_];
  //拷贝数据
  for (int i = 0; i < size_; i++) {
    //如果是自定义的复杂数据类型，必须对 = 运算赋进行重载,  operator=
    this->data_[i] = std::move(arr.data_[i]);
  }

  std::cout << "调用 = 移动赋值操作 " << std::endl;
  return *this;
}

template<typename T>
T &MyArray<T>::operator[](int index) {
  if (index < 0 || index >= size_) {
    std::cout << "[] fail. Index is illegal." << std::endl;
    throw "[] fail. Index is illegal.";
  }
  std::cout << "[] 调用" << std::endl;
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
    throw "Add fail. Index is illegal.";
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
void MyArray<T>::Set(int index, T t) {
  if (index < 0 || index >= size_) {
    std::cout << "Set Fail. Index is illegal." << std::endl;
    throw "Set fail. Index is illegal.";
  }
  if (IsEmpty()) {
    std::cout << "Set Fail. Array is empty." << std::endl;
    throw "Set fail. Array is empty.";
  }
  data_[index] = t;
}

template<typename T>
void MyArray<T>::AddLast(T t) {
  Add(size_, t);
}

template<typename T>
T MyArray<T>::Get(int index) const {
  if (index < -1 || index >= size_) {
    std::cout << "Get fail. Index is illegal." << std::endl;
    throw "Get fail. Index is illegal.";
  }
  if (IsEmpty()) {
    std::cout << "Get fail. Array is empty." << std::endl;
    throw "Get fail. Array is empty.";
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
    throw "Remove fail. Index is illegal.";
  }
  if (IsEmpty()) {
    std::cout << "Remove fail. Array is empty." << std::endl;
    throw "Remove fail. Array is empty.";
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
int MyArray<T>::Find(T t) const {
  if (IsEmpty()) {
    std::cout << "Find fail. Array is empty." << std::endl;
    throw "Find Fail. Array is empty";
  }
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
  if (new_capacity <= 0){
    std::cout << "Resize fail. New_capacity is illegal." << std::endl;
    throw "Resize fail. New_capacity is illegal.";
  }
  T *new_data = new T[new_capacity];
  for (int i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
  std::cout << "Resize Capacity = " << new_capacity << std::endl;
}


#endif //DATA_STRUCTURE_ARRAYS_SRC_MYARRAY_H_
