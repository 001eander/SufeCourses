/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 3
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "myqueue.cpp"
#include "myqueue.h"
#include "simpio.h"

int main() {
  MyQueue<int> queue;
  std::cout << "Enqueuing elements: 10, 20, 30" << std::endl;
  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);
  std::cout << "Queue size: " << queue.size() << std::endl;
  std::cout << "Front element: " << queue.peek() << std::endl;

  std::cout << "Dequeuing elements:" << std::endl;
  while (!queue.isEmpty()) {
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
  }
  std::cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No")
            << std::endl;

  std::cout << "Enqueuing elements: 100, 200" << std::endl;
  queue.enqueue(100);
  queue.enqueue(200);
  std::cout << "Queue size: " << queue.size() << std::endl;
  queue.clear();
  std::cout << "After clear(), queue size: " << queue.size() << std::endl;
  return EXIT_SUCCESS;
}
