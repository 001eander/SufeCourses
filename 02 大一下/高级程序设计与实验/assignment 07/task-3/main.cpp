/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "qk.h"
#include "simpio.h"
#include "vector.h"

int main() {
  Vector<int> a;

  std::cin >> a;
  auto k = getInteger();

  if (k < 0 || k >= a.size()) {
    std::cerr << "Index out of range" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << std::format("kth element: {}", q_kth_(a, k)) << std::endl;
  return EXIT_SUCCESS;
}
