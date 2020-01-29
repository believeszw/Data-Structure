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
  ArrayQueue(int capacity);
  ArrayQueue(const ArrayQueue<T> &obj);


  ~ArrayQueue();

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
  my_array_ = new MyArray<T>(10);
}

template<typename T>
ArrayQueue<T>::ArrayQueue(int capacity) {
  my_array_ = new MyArray<T>(capacity);
}

template<typename T>
ArrayQueue<T>::~ArrayQueue() {
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

}

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_ARRAY_QUEUE_H_
