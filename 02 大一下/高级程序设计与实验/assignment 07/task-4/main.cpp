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

#include "bisearch.h"
#include "console.h"
#include "simpio.h"

int main() {
  Vector<int> seq;
  std::cin >> seq;

  auto x = getInteger();

  std::cout << q_find_(seq, x) << std::endl;

  return EXIT_SUCCESS;
}
