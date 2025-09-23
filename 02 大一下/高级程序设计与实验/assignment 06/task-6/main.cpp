/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * 并查集（路径压缩）
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "map.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

class UnionFindSet {
 private:
  Map<size_t, size_t> parent;

 public:
  UnionFindSet() = default;
  ~UnionFindSet() = default;

  size_t find_parent(size_t p) {
    if (!parent.containsKey(p))
      parent[p] = p;
    else if (parent[p] != p)
      parent[p] = find_parent(parent[p]);
    return parent[p];
  }

  size_t add_relationship(size_t p, size_t s) {
    auto root_p = find_parent(p);
    auto root_s = find_parent(s);
    if (root_p != root_s) parent[root_s] = root_p;
    return root_p;
  }

  Map<size_t, Set<size_t>> get_structure() {
    Map<size_t, Set<size_t>> structure;
    for (size_t i = 0; i < parent.size(); ++i) {
      auto root = find_parent(i);
      if (!structure.containsKey(root)) structure[root] = Set<size_t>();
      structure[root].add(i);
    }
    for (auto parent : structure) structure[parent].remove(parent);
    return structure;
  }
};

int main() {
  auto m = getInteger("Enter the number of relationships: ");

  UnionFindSet ufs;
  for (size_t i = 0; i < m; ++i) {
    auto p = getInteger("Enter the first person: ");
    auto s = getInteger("Enter the second person: ");
    ufs.add_relationship(p, s);
  }

  auto n = getInteger("Enter the number of the person: ");
  std::cout << std::format("The final leader of the person {} is {}.", n,
                           ufs.find_parent(n))
            << std::endl;

  auto structure = ufs.get_structure();
  std::cout << "The structure of the relationship is:" << std::endl;
  for (auto leader : structure)
    std::cout << std::format("Leader: {} -> ", leader) << structure[leader]
              << std::endl;

  return EXIT_SUCCESS;
}
