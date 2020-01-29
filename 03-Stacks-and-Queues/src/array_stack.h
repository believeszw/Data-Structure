//
// Created by believe on 2020/1/20.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_

#include "my_array.h"
#include "i_stack.h"

template<typename T>
class ArrayStack : public IStack<T> {
  MyArray<T> *my_array_{nullptr};
 public:
  ArrayStack();
  explicit ArrayStack(int capacity);
  ArrayStack(const ArrayStack<T> &obj);
  ArrayStack<T> &operator= (const ArrayStack<T> &obj);
  ArrayStack(ArrayStack<T> &&obj) noexcept;
  ArrayStack<T> &operator= (ArrayStack<T> &&obj) noexcept;
  ~ArrayStack();

  friend std::ostream &operator<<(std::ostream &out, ArrayStack<T> &obj) {
    out << "Stack: [ ";
    for (int kI = 0; kI < obj.GetSize(); ++kI) {
      out << obj.my_array_->Get(kI);
      if (kI != obj.GetSize() - 1) {
        out << ", ";
      }
    }
    out << " ] top";
    return out;
  }

  int GetSize() const final;
  bool IsEmpty() final;
  void Push(T t) final;
  T Pop() final;
  T Peek() const final;
  int GetCapacity() const;
  void Clear();
};

template<typename T>
ArrayStack<T>::ArrayStack() {
  std::cout << "调用 ArrayStack() 构造" << std::endl;
  my_array_ = new MyArray<T>();
}

template<typename T>
ArrayStack<T>::ArrayStack(int capacity) {
  std::cout << "调用 ArrayStack(int capacity) 构造" << std::endl;
  my_array_ = new MyArray<T>(capacity);
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
  std::cout << "调用 ~ArrayStack() 析构" << std::endl;
  delete my_array_;
  my_array_ = nullptr;
}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &obj) {
  std::cout << "调用 ArrayStack(const ArrayStack<T> &obj) 拷贝构造" << std::endl;
  this->my_array_ = new MyArray<T>(*obj.my_array_);
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack<T> &obj) {
  std::cout << "调用 ArrayStack = 赋值" << std::endl;
  *this->my_array_ = *obj.my_array_;
  return *this;
}

template<typename T>
ArrayStack<T>::ArrayStack(ArrayStack<T> &&obj) noexcept{
  std::cout << "调用 ArrayStack(const ArrayStack<T> &&obj) 移动拷贝构造" << std::endl;
  this->my_array_ = new MyArray<T>(std::move(*obj.my_array_));
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(ArrayStack<T> &&obj) noexcept{
  std::cout << "调用 ArrayStack = 移动赋值" << std::endl;
  *this->my_array_ = std::move(*obj.my_array_);
  return *this;
}

template<typename T>
int ArrayStack<T>::GetSize() const {
  return my_array_->GetSize();
}

template<typename T>
bool ArrayStack<T>::IsEmpty() {
  return my_array_->IsEmpty();
}

template<typename T>
void ArrayStack<T>::Push(T t) {
  my_array_->AddLast(t);
}

template<typename T>
T ArrayStack<T>::Pop() {
  return my_array_->RemoveLast();
}

template<typename T>
T ArrayStack<T>::Peek() const {
  return my_array_->GetLast();
}

template<typename T>
void ArrayStack<T>::Clear() {
  my_array_->Clear();
}
template<typename T>
int ArrayStack<T>::GetCapacity() const {
  return my_array_->GetCapacity();
}

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_
