//
// Created by believe on 2020/4/14.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_

#include "i_quque.hpp"
#include "my_array.hpp"

template <typename T> class LoopQueue : public IQueue<T> {
private:
  T *data_{nullptr};
  int front_{0};
  int tail_{0};
  int capacity_{0};

public:
  LoopQueue();
  explicit LoopQueue(int capacity);
  LoopQueue(const LoopQueue<T> &obj);
  LoopQueue<T> &operator=(const LoopQueue<T> &obj);
  LoopQueue(LoopQueue<T> &&obj) noexcept;
  LoopQueue<T> &operator=(LoopQueue<T> &&obj) noexcept;
  ~LoopQueue();
  int GetSize() const final;
  int GetCapacity() const final;
  bool IsEmpty() final;
  void Enqueue(T t) final;
  T Dequeue() final;
  T GetFront() const final;
  void Clear();
  void resize(int newCapacity);
};
template <typename T> LoopQueue<T>::LoopQueue() {
  std::cout << "调用 LoopQueue() 构造" << std::endl;
  data_ = new T[11];
  front_ = tail_ = 0;
  capacity_ = 10;
}
template <typename T> LoopQueue<T>::LoopQueue(int capacity) {
  std::cout << "调用 LoopQueue(int capacity) 构造" << std::endl;
  data_ = new T[capacity + 1];
  front_ = tail_ = 0;
  capacity_ = capacity;
}
template <typename T> LoopQueue<T>::LoopQueue(const LoopQueue<T> &obj) {
  std::cout << "调用 LoopQueue(const LoopQueue<T> &obj) 构造" << std::endl;
  data_ = new T[obj.capacity_ + 1];
  front_ = tail_ = 0;
  capacity_ = obj.capacity_;
  for (int i = 0; i < obj.capacity_; ++i) {
    data_[i] = obj.data_[i];
  }
}
template <typename T>
LoopQueue<T> &LoopQueue<T>::operator=(const LoopQueue<T> &obj) {
  std::cout << "调用 LoopQueue(const LoopQueue<T> &obj) = 构造" << std::endl;
  if (this != &obj) {
    delete[] data_;
    data_ = new T[obj.capacity_ + 1];
    front_ = tail_ = 0;
    capacity_ = obj.capacity_;
    for (int i = 0; i < obj.capacity_; ++i) {
      data_[i] = obj.data_[i];
    }
  }
  return *this;
}
template <typename T> LoopQueue<T>::LoopQueue(LoopQueue<T> &&obj) noexcept {
  std::cout << "调用 LoopQueue(LoopQueue<T> &&obj) noexcept 构造" << std::endl;
  data_ = obj.data_;
  front_ = obj.front_;
  tail_ = obj.tail_;
  capacity_ = obj.capacity_;
  obj.data_ = nullptr;
  obj.front_ = 0;
  obj.tail_ = 0;
  obj.capacity_ = 0;
}
template <typename T>
LoopQueue<T> &LoopQueue<T>::operator=(LoopQueue<T> &&obj) noexcept {
  std::cout << "调用 LoopQueue(LoopQueue<T> &&obj) = 构造" << std::endl;
  if (this != &obj) {
    delete[] data_;
    data_ = obj.data_;
    front_ = obj.front_;
    tail_ = obj.tail_;
    capacity_ = obj.capacity_;
    obj.data_ = nullptr;
    obj.front_ = 0;
    obj.tail_ = 0;
    obj.capacity_ = 0;
  }
  return *this;
}
template <typename T> LoopQueue<T>::~LoopQueue() {
  std::cout << "调用 ~LoopQueue() 析构" << std::endl;
  delete data_;
  data_ = nullptr;
  front_ = 0;
  tail_ = 0;
}
template <typename T> int LoopQueue<T>::GetSize() const {
  return tail_ > front_ ? tail_ - front_ : tail_ + capacity_ - front_;
}
template <typename T> int LoopQueue<T>::GetCapacity() const {
  return capacity_;
}
template <typename T> bool LoopQueue<T>::IsEmpty() { return front_ == tail_; }
template <typename T> T LoopQueue<T>::Dequeue() {
  if (IsEmpty())
    return T{};

  auto ret = data_[front_];
  front_ = (front_ + 1) % capacity_;
  if (GetSize() == capacity_ / 4 && capacity_ / 2 != 0)
    resize(capacity_ / 2);
  return ret;
}
template <typename T> void LoopQueue<T>::Enqueue(T t) {
  if (capacity_ == 0) {
    return;
  }
  if ((tail_ + 1) % capacity_ == front_)
    resize(capacity_ * 2);

  data_[tail_] = t;
  tail_ = (tail_ + 1) % capacity_;
}
template <typename T> T LoopQueue<T>::GetFront() const { return data_[front_]; }
template <typename T> void LoopQueue<T>::Clear() { front_ = tail_ = 0; }
template <typename T> void LoopQueue<T>::resize(int newCapacity) {
  auto newData = new T[newCapacity + 1];
  int sz = GetSize();
  for (int i = 0; i < sz; i++)
    newData[i] = data_[(i + front_) % capacity_];

  data_ = newData;
  front_ = 0;
  tail_ = sz;
}

#endif // DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_
