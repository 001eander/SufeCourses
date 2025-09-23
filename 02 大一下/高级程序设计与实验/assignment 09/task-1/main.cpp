/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "hashmap.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

struct Edge {
  int from;
  int to;
};

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
  os << std::format("({},{})", edge.from, edge.to);
  return os;
}

typedef Edge Domino;
typedef Vector<int> Path;

void print_path(const Path& path) {
  for (size_t i = 0; i < path.size(); i++) {
    if (i > 0) std::cout << " -> ";
    std::cout << path[i];
  }
  std::cout << std::endl;
}

struct Graph {
  Set<int> vertices;
  Vector<Edge> edges;

  Graph(const Vector<Edge>& e) {
    for (const auto& edge : e) {
      vertices += edge.from, edge.to;
      edges += edge;
    }
  }
};

Vector<int> get_odd_nodes(const Graph& g) {
  int deg[6 + 1]{0};
  for (const auto& edge : g.edges) {
    deg[edge.from]++;
    deg[edge.to]++;
  }
  Vector<int> odd_nodes;
  for (const auto& vertex : g.vertices)
    if (deg[vertex] % 2 == 1) odd_nodes.add(vertex);
  return odd_nodes;
}

Vector<Path> _dfs(int node, const Path& path, const Graph& g, bool vis[]) {
  auto flag = true;
  for (size_t i = 0; i < g.edges.size() && flag; i++) flag &= vis[i];
  if (flag) {
    Vector<Path> result;
    result.add(path);
    return result;
  }

  Vector<Path> result;
  for (size_t i = 0; i < g.edges.size(); i++) {
    if (vis[i]) continue;
    auto edge = g.edges[i];
    if (node == edge.from || node == edge.to) {
      auto nxt = (node == edge.from) ? edge.to : edge.from;
      vis[i] = true;
      auto new_path = path;
      new_path += nxt;
      result += _dfs(nxt, new_path, g, vis);
      vis[i] = false;
    }
  }
  return result;
}

Vector<Path> get_chains(const Vector<Domino>& dominos) {
  Graph g(dominos);
  auto odd_nodes = get_odd_nodes(g);
  if (odd_nodes.size() != 0 && odd_nodes.size() != 2) return {};

  Vector<Path> paths{};
  bool vis[6 + 1]{false};
  if (odd_nodes.size() == 0)
    for (const auto& v : g.vertices) paths += _dfs(v, {v}, g, vis);
  else
    for (const auto& v : odd_nodes) paths += _dfs(v, {v}, g, vis);
  return paths;
}

int main() {
  Vector<Domino> dominos{{2, 1}, {4, 2}, {3, 3}, {3, 4}, {1, 4}};
  auto chains = get_chains(dominos);

  if (chains.isEmpty()) {
    std::cout << "No chains found" << std::endl;
    return EXIT_SUCCESS;
  }

  std::cout << std::format("Found {} chains", chains.size()) << std::endl;
  std::cout << "Chains:" << std::endl;
  for (const auto& path : chains) print_path(path);
  return EXIT_SUCCESS;
}
