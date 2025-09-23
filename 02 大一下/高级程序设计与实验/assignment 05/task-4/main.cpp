/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 4
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "queue.h"
#include "simpio.h"
#include "stack.h"

template <typename T>
void reverse(Stack<T>& x, size_t n) {
  Queue<T> y;
  for (size_t i = 0; i < n; ++i) y.enqueue(x.pop());
  for (size_t i = 0; i < n; ++i) x.push(y.dequeue());
}

template <typename T>
void reverse(Queue<T>& x, size_t n) {
  Queue<T> tmp;
  Stack<T> y;
  for (size_t i = 0; i < n; ++i) y.push(x.dequeue());
  while (!x.isEmpty()) tmp.enqueue(x.dequeue());
  for (size_t i = 0; i < n; ++i) x.enqueue(y.pop());
  while (!tmp.isEmpty()) x.enqueue(tmp.dequeue());
}

template <typename T>
void rotate(Stack<T>& x, size_t n, size_t k) {
  Queue<T> y;
  for (size_t i = 0; i < n; ++i) y.enqueue(x.pop());
  while (k--) {
    auto t = y.dequeue();
    y.enqueue(t);
  }
  Stack<T> tmp;
  while (!y.isEmpty()) tmp.push(y.dequeue());
  while (!tmp.isEmpty()) x.push(tmp.pop());
}

template <typename T>
void rotate(Queue<T>& x, size_t n, size_t k) {
  Queue<T> y;
  for (size_t i = 0; i < n; ++i) y.enqueue(x.dequeue());
  while (k--) {
    auto t = y.dequeue();
    y.enqueue(t);
  }
  Queue<T> tmp;
  while (!x.isEmpty()) tmp.enqueue(x.dequeue());
  while (!y.isEmpty()) x.enqueue(y.dequeue());
  while (!tmp.isEmpty()) x.enqueue(tmp.dequeue());
}

int main() {
  auto n = 3ull;
  auto k = 2ull;
  auto stk = Stack<int>();
  auto que = Queue<int>();
  for (size_t i = 0; i < 5; ++i) {
    stk.push(i + 1);
    que.enqueue(i + 1);
  }

  std::cout << "Stack before reverse: " << stk.toString() << std::endl;
  reverse(stk, n);
  std::cout << "Stack after reverse: " << stk.toString() << std::endl;

  std::cout << "Queue before reverse: " << que.toString() << std::endl;
  reverse(que, n);
  std::cout << "Queue after reverse: " << que.toString() << std::endl;

  std::cout << "Stack before rotate: " << stk.toString() << std::endl;
  rotate(stk, n, k);
  std::cout << "Stack after rotate: " << stk.toString() << std::endl;

  std::cout << "Queue before rotate: " << que.toString() << std::endl;
  rotate(que, n, k);
  std::cout << "Queue after rotate: " << que.toString() << std::endl;
  return EXIT_SUCCESS;
}
