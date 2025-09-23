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
#include "set.h"
#include "simpio.h"
#include "vector.h"

struct SubVector {
  Vector<int> vec;
  int64_t sum;
};

std::ostream& operator<<(std::ostream& os, const SubVector& sv) {
  return os << "SubVector: { vec: " << sv.vec << ", sum: " << sv.sum << " }";
}

bool operator<(const SubVector& lhs, const SubVector& rhs) {
  if (lhs.sum == rhs.sum) return lhs.vec < rhs.vec;
  return lhs.sum < rhs.sum;
}

Set<SubVector> get_subvectors(const Vector<int>& vec) {
  if (vec.isEmpty()) return Set<SubVector>{{{}, 0}};

  auto subvecs = get_subvectors(vec.subList(1));
  auto result = subvecs;
  for (const auto& subvec : subvecs)
    result += SubVector{vec.subList(0, 1) + subvec.vec, subvec.sum + vec[0]};
  return result;
}

Set<int64_t> get_sums(const Vector<int>& vec) {
  Set<SubVector> subvecs = get_subvectors(vec);
  Set<int64_t> sums;
  for (const auto& subvec : subvecs) sums += subvec.sum;
  return sums;
}

bool contain_subsum(const Vector<int>& vec, int64_t target) {
  Set<int64_t> sums = get_sums(vec);
  return sums.contains(target);
}

Set<SubVector> get_subvectors(const Vector<int>& vec, int64_t target) {
  Set<SubVector> subvecs = get_subvectors(vec);
  Set<SubVector> result;
  for (const auto& subvec : subvecs)
    if (subvec.sum == target) result += subvec;
  return result;
}

Set<SubVector> get_biggest_leq_subvector(const Vector<int>& vec,
                                         int64_t target) {
  Set<SubVector> subvecs = get_subvectors(vec);
  Set<SubVector> result;
  for (const auto& subvec : subvecs) {
    if (result.isEmpty() && subvec.sum <= target) {
      result += subvec;
    } else if (subvec.sum <= target && subvec.sum > result.first().sum) {
      result.clear();
      result += subvec;
    } else if (subvec.sum == result.first().sum) {
      result += subvec;
    }
  }
  return result;
}

int main() {
  std::cout << "All possible sums:\n";
  std::cout << get_sums({2, 3, 5, 23}) << std::endl;

  std::cout << "Contains subvector with sum " << 23 << ": "
            << (contain_subsum({2, 3, 5, 23}, 23) ? "true" : "false") << "\n";

  std::cout << "Subvectors with sum " << 23 << ":\n";
  for (const auto& subvec : get_subvectors({2, 3, 5, 23}, 23))
    std::cout << "  " << subvec << "\n";

  std::cout << "Biggest subvector with sum <= " << 24 << ":\n";
  for (const auto& subvec : get_biggest_leq_subvector({2, 3, 5, 23}, 24))
    std::cout << "  " << subvec << "\n";

  return EXIT_SUCCESS;
}
