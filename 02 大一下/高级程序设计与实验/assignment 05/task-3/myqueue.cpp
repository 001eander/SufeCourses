#include "myqueue.h"

#include "iostream"

template <typename T>
void MyQueue<T>::main2tmp() {
  while (!stk.isEmpty()) _stk.push(stk.pop());
}

template <typename T>
void MyQueue<T>::tmp2main() {
  while (!_stk.isEmpty()) stk.push(_stk.pop());
}

template <typename T>
T MyQueue<T>::dequeue() {
  if (stk.isEmpty()) {
    std::cerr << "Queue is empty, cannot dequeue." << std::endl;
    return T();
  }
  main2tmp();
  T value = _stk.pop();
  tmp2main();
  return value;
}

template <typename T>
T MyQueue<T>::peek() {
  if (stk.isEmpty()) {
    std::cerr << "Queue is empty, cannot peek." << std::endl;
    return T();
  }
  main2tmp();
  T value = _stk.peek();
  tmp2main();
  return value;
}

template <typename T>
void MyQueue<T>::enqueue(const T& value) {
  stk.push(value);
}

template <typename T>
bool MyQueue<T>::isEmpty() const {
  return stk.isEmpty();
}

template <typename T>
int MyQueue<T>::size() const {
  return stk.size();
}

template <typename T>
void MyQueue<T>::clear() {
  stk.clear();
}