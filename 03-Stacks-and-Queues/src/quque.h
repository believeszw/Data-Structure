//
// Created by believe on 2020/1/22.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_QUQUE_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_QUQUE_H_

template <typename T>
class IQueue {
  virtual int GetSize() = 0;
  virtual bool IsEmpty() = 0;
  virtual void Enqueue(T t) = 0;
  virtual T Dequeue() = 0;
  virtual T GetFront() = 0;
};

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_QUQUE_H_
