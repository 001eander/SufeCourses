/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 2
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "map.h"
#include "simpio.h"
#include "vector.h"

typedef Vector<int> Set;

int sum(const Set& set) {
  int s = 0;
  for (int item : set) s += item;
  return s;
}

Map<int, Vector<Set>> get_subsets(const Set& set) {
  Map<int, Vector<Set>> subsets{};
  for (uint64_t stage = 0; stage < (1ull << set.size()); ++stage) {
    Set subset{};
    for (int j = 0; j < set.size(); ++j)
      if (stage & (1ull << j)) subset += set[j];
    subsets[sum(subset)] += subset;
  }
  return subsets;
}

int main() {
  Set set{};
  std::cin >> set;
  auto subsets = get_subsets(set);

  auto s = getInteger();

  std::cout << "Q1: " << subsets[s] << std::endl;

  auto ps = s - 1;
  while (!subsets.containsKey(ps)) ps--;
  std::cout << "Q2: " << subsets[ps] << std::endl;

  Vector<Set> smallest_subsets{};
  for (Set subset : subsets[s]) {
    if (!smallest_subsets.isEmpty() &&
        (subset.size() > smallest_subsets[0].size()))
      continue;
    if (!smallest_subsets.isEmpty() &&
        (subset.size() < smallest_subsets[0].size()))
      smallest_subsets.clear();
    smallest_subsets += subset;
  }
  std::cout << "Q3: " << smallest_subsets << std::endl;

  return EXIT_SUCCESS;
}
