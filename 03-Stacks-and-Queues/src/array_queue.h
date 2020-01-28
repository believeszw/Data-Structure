//
// Created by believe on 2020/1/22.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_

#include "i_quque.h"
#include "my_array.h"

template <typename T>
class ArrayQueue : public IQueue<T> {
  MyArray<T> *my_array_;
  int front_;
  int tail_;
  int size_;
  int capacity_;
 public:
  ArrayQueue();
  ArrayQueue(int capacity);
  ~ArrayQueue();

  int GetSize() final;
  bool IsEmpty() final;
  void Enqueue(T t) final;
  T Dequeue() final;
  T GetFront() final;
};
template<typename T>
ArrayQueue<T>::ArrayQueue() {

}

template<typename T>
ArrayQueue<T>::ArrayQueue(int capacity) {

}

template<typename T>
ArrayQueue<T>::~ArrayQueue() {

}

template<typename T>
int ArrayQueue<T>::GetSize() {
  return my_array_->GetSize();
}

template<typename T>
bool ArrayQueue<T>::IsEmpty() {
  return my_array_->IsEmpty();
}

template<typename T>
void ArrayQueue<T>::Enqueue(T t) {

}

template<typename T>
T ArrayQueue<T>::Dequeue() {
  return nullptr;
}

template<typename T>
T ArrayQueue<T>::GetFront() {
  return nullptr;
}


#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_
