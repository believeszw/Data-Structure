//
// Created by believe on 2020/1/20.
//

#ifndef DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_I_STACK_H_
#define DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_I_STACK_H_

template <typename T>
class IStack {
 public:
  virtual int GetSize() const = 0;
  virtual int GetCapacity() const = 0;
  virtual bool IsEmpty() = 0;
  virtual void Push (T t) = 0;
  virtual T Pop() = 0;
  virtual T Peek() const = 0;
};

#endif //DATA_STRUCTURE_03_STACKS_AND_QUEUES_SRC_I_STACK_H_
