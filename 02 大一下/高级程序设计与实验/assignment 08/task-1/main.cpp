/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

typedef Set<Vector<int>> ResultSet;

ResultSet choose_from(const Vector<int>& vec, int k, bool ordered) {
  if (k == 0) return {{}};
  if (vec.isEmpty()) return {};

  auto result = choose_from(vec.subList(0, vec.size() - 1), k, ordered);
  for (const auto& item :
       choose_from(vec.subList(0, vec.size() - 1), k - 1, ordered)) {
    result += item + vec[vec.size() - 1];
    if (ordered) {
      auto new_item = Vector<int>{vec[vec.size() - 1]} + item;
      result += new_item;
    }
  }

  return result;
}

void print_result(const ResultSet& result) {
  auto col_cnt = 0;
  for (const auto& item : result) {
    std::cout << item << " ";
    if (++col_cnt % 5 == 0) std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  Vector<int> vec{1, 2, 4, 4, 5, 3, 3};
  int k = 3;

  std::cout << "Function 1: ordered\n";
  auto result = choose_from(vec, k, true);
  print_result(result);

  std::cout << "Function 2: unordered\n";
  result = choose_from(vec, k, false);
  print_result(result);

  return EXIT_SUCCESS;
}
