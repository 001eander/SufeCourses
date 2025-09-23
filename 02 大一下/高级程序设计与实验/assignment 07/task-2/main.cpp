/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cstdint>
#include <cstdlib>

#include "console.h"
#include "merge.h"
#include "simpio.h"
#include "vector.h"

int main() {
  Vector<int> vec;
  std::cin >> vec;

  auto [cnt, sorted_vec] = merge_reverse_pair_cnt(vec);

  std::cout << "Reverse pair count: " << cnt << std::endl;
  std::cout << "Sorted vector: " << sorted_vec << std::endl;
  return EXIT_SUCCESS;
}
