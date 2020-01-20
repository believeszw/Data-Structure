//
// Created by SZW on 2020/1/20.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_

#include "my_array.h"
#include "stack.h"

template<typename T>
class ArrayStack : public Stack<T> {
 private:
  MyArray<T> *my_array_;
 public:
  ArrayStack();
  explicit ArrayStack(int capacity);
  ArrayStack(const ArrayStack<T> &obj);
  ArrayStack<T> &operator= (const ArrayStack<T> &obj);
  ArrayStack(ArrayStack<T> &&obj) noexcept;
  ArrayStack<T> &operator= (ArrayStack<T> &&obj) noexcept;
  T &operator[](int index);
  ~ArrayStack();

  virtual int GetSize();
  virtual bool IsEmpty();
  virtual void Push(T t);
  virtual T Pop();
  virtual T Peek();
  void Clear();
};

template<typename T>
ArrayStack<T>::ArrayStack() {
  my_array_ = new MyArray<T>();
}

template<typename T>
ArrayStack<T>::ArrayStack(int capacity) {
  my_array_ = new MyArray<T>(capacity);
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
  delete my_array_;
  my_array_ = nullptr;
}

template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &obj) {
  this->my_array_ = new MyArray<T>(*obj.my_array_);
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(const ArrayStack<T> &obj) {
  *this->my_array_ = *obj.my_array_;
  return *this;
}

template<typename T>
ArrayStack<T>::ArrayStack(ArrayStack<T> &&obj) noexcept{
  this->my_array_ = new MyArray<T>(std::move(*obj.my_array_));
}

template<typename T>
ArrayStack<T> &ArrayStack<T>::operator=(ArrayStack<T> &&obj) noexcept{
  *this->my_array_ = std::move(*obj.my_array_);
  return *this;
}

template<typename T>
T &ArrayStack<T>::operator[](int index) {
  return (*my_array_)[index];
}

template<typename T>
int ArrayStack<T>::GetSize() {
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
T ArrayStack<T>::Peek() {
  return my_array_->GetLast();
}

template<typename T>
void ArrayStack<T>::Clear() {
  my_array_->Clear();
}


#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAYSTACK_H_
