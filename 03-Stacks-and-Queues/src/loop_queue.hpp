//
// Created by believe on 2020/4/14.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_

#include "my_array.hpp"
#include "i_quque.hpp"

template<typename T>
class LoopQueue : public IQueue<T> {
 private:
  T *data_{nullptr};
  int front_{0};
  int tail_{0};
  int capacity_{0};
 public:
  LoopQueue();
  explicit LoopQueue(int capacity);
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
template<typename T>
LoopQueue<T>::LoopQueue() {
  std::cout << "调用 LoopQueue() 构造" << std::endl;
    LoopQueue(10);
}
template<typename T>
LoopQueue<T>::LoopQueue(int capacity) {
  std::cout << "调用 LoopQueue(int capacity) 构造" << std::endl;
  data_ = new T[capacity + 1];
  front_ = tail_ = 0;
  capacity_ = capacity;
}
template<typename T>
LoopQueue<T>::~LoopQueue() {
  std::cout << "调用 ~LoopQueue() 析构" << std::endl;
  delete data_;
  data_ = nullptr;
  front_ = 0;
  tail_ = 0;
}
template<typename T>
int LoopQueue<T>::GetSize() const {
  return tail_ > front_ ? tail_ - front_ : tail_ + capacity_ - front_;
}
template<typename T>
int LoopQueue<T>::GetCapacity() const {
  return capacity_;
}
template<typename T>
bool LoopQueue<T>::IsEmpty() {
  return front_ == tail_;
}
template<typename T>
T LoopQueue<T>::Dequeue() {
    if(IsEmpty())
        return T{};

    auto ret = data_[front_];
    front_ = (front_ + 1) % GetCapacity();
    if(GetSize() == GetCapacity() / 4 && GetCapacity() / 2 != 0)
        resize(GetCapacity() / 2);
    return ret;
}
template<typename T>
void LoopQueue<T>::Enqueue(T t) {
    if((tail_ + 1) % GetCapacity() == front_)
        resize(GetCapacity() * 2);

    data_[tail_] = t;
    tail_ = (tail_ + 1) % GetCapacity();
}
template<typename T>
T LoopQueue<T>::GetFront() const {
  return data_[front_];
}
template<typename T>
void LoopQueue<T>::Clear() {
   front_ = tail_ = 0;
}
template<typename T>
void LoopQueue<T>::resize(int newCapacity) {
    auto newData = new T[newCapacity + 1];
    int sz = GetSize();
    for(int i = 0 ; i < sz ; i ++)
        newData[i] = data_[(i + front_) % GetCapacity()];

    data_ = newData;
    front_ = 0;
    tail_ = sz;
}

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_LOOP_QUEUE_H_
