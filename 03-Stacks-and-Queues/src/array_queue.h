//
// Created by believe on 2020/1/22.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_

#include "i_quque.h"
#include "my_array.h"

template <typename T>
class ArrayQueue : public IQueue<T> {
  MyArray<T> *my_array_{nullptr};
 public:
  ArrayQueue();
  explicit ArrayQueue(int capacity);
  ArrayQueue(const ArrayQueue<T> &obj);
  ArrayQueue<T> &operator=(const ArrayQueue<T> &obj);
  ArrayQueue(ArrayQueue<T> &&obj) noexcept;
  ArrayQueue<T> &operator=(ArrayQueue<T> &&obj) noexcept ;
  ~ArrayQueue();

  friend std::ostream &operator<<(std::ostream &out, const ArrayQueue<T> &obj) {
    out << "ArrayQueue: [ ";
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
  void Enqueue(T t) final;
  T Dequeue() final;
  T GetFront() const final;
  void Clear();
  int GetCapacity() const;
};
template<typename T>
ArrayQueue<T>::ArrayQueue() {
  std::cout << "调用 ArrayQueue() 构造" << std::endl;
  my_array_ = new MyArray<T>(10);
}

template<typename T>
ArrayQueue<T>::ArrayQueue(int capacity) {
  std::cout << "调用 ArrayQueue(int capacity) 构造" << std::endl;
  my_array_ = new MyArray<T>(capacity);
}

template<typename T>
ArrayQueue<T>::~ArrayQueue() {
  std::cout << "调用 ~ArrayQueue() 析构" << std::endl;
  delete my_array_;
  my_array_ = nullptr;
}

template<typename T>
int ArrayQueue<T>::GetSize() const {
  return my_array_->GetSize();
}

template<typename T>
bool ArrayQueue<T>::IsEmpty() {
  return my_array_->IsEmpty();
}

template<typename T>
void ArrayQueue<T>::Enqueue(T t) {
  my_array_->AddLast(t);
}

template<typename T>
T ArrayQueue<T>::Dequeue() {
  return my_array_->RemoveFirst();
}

template<typename T>
T ArrayQueue<T>::GetFront() const {
  return my_array_->GetFirst();
}

template<typename T>
void ArrayQueue<T>::Clear() {
  my_array_->Clear();
}
template<typename T>
int ArrayQueue<T>::GetCapacity() const {
  return my_array_->GetCapacity();
}
template<typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &obj) {
  std::cout << "调用 ArrayQueue(const ArrayQueue<T> &obj) 拷贝构造" << std::endl;
  this->my_array_ = new MyArray<T>(*obj.my_array_);
}
template<typename T>
ArrayQueue<T> &ArrayQueue<T>::operator=(const ArrayQueue<T> &obj) {
  std::cout << "调用 ArrayQueue = 赋值" << std::endl;
  *this->my_array_ = *obj.my_array_;
  return *this;
}
template<typename T>
ArrayQueue<T>::ArrayQueue(ArrayQueue<T> &&obj) noexcept {
  std::cout << "调用 ArrayQueue(ArrayQueue<T> &&obj) 移动拷贝构造" << std::endl;
  this->my_array_ = new MyArray<T>(std::move(*obj.my_array_));
}
template<typename T>
ArrayQueue<T> &ArrayQueue<T>::operator=(ArrayQueue<T> &&obj) noexcept {
  std::cout << "调用 ArrayQueue = 移动赋值" << std::endl;
  *this->my_array_ = std::move(*obj.my_array_);
  return *this;
}

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_
