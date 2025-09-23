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
#include "set.h"
#include "simpio.h"

template <typename Type>
Type f(Type x) {
  Type res = 0;
  while (x) {
    res += (x % 10) * (x % 10);
    x /= 10;
  }
  return res;
}

int main() {
  auto n = getInteger("Enter a number: ");

  Set<int> seen;
  while (!seen.contains(n)) {
    seen.add(n);
    std::cout << n << " -> ";
    n = f(n);
  }
  std::cout << n << std::endl;

  return EXIT_SUCCESS;
}
