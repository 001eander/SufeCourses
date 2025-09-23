#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "stack.h"

template <typename T>
class MyQueue {
 private:
  Stack<T> stk, _stk;
  void main2tmp();
  void tmp2main();

 public:
  MyQueue() = default;
  ~MyQueue() = default;

  T dequeue();
  T peek();
  void enqueue(const T& value);
  bool isEmpty() const;
  int size() const;
  void clear();
};

#endif  // MYQUEUE_H
