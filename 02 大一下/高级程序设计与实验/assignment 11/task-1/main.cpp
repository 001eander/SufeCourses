/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Task 1
 */

#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "direction.h"
#include "grid.h"
#include "queue.h"
#include "simpio.h"

int main() {
  std::ifstream fin("./testcase0.txt");
  size_t x, y;
  fin >> x >> y;
  GridLocation start(x, y);
  fin >> x >> y;
  GridLocation target(x, y);
  size_t row, col;
  fin >> row >> col;

  Grid<bool> map(row, col, false);
  for (size_t i = 0; i < row; ++i) {
    std::string s{};
    fin >> s;
    for (size_t j = 0; j < col; ++j)
      if (s[j] == '0') map[i][j] = true;
  }

  Grid<char> result(row, col);
  for (auto pos : result.locations()) result[pos] = (map[pos] ? '0' : '1');

  Grid<GridLocation> prev(row, col);
  for (auto pos : prev.locations()) prev[pos] = pos;

  Queue<GridLocation> q{start};
  while (!q.isEmpty()) {
    auto p = q.dequeue();

    if (!map[p]) continue;
    map[p] = false;

    int dx[]{0, 1, 0, -1}, dy[]{1, 0, -1, 0};
    for (size_t d = 0; d < 4; ++d) {
      GridLocation pos(p.row + dx[d], p.col + dy[d]);
      if (!map.inBounds(pos) || !map[pos]) continue;
      q.enqueue(pos);
      prev[pos] = p;
    }
  }

  if (prev[target] == target) {
    std::cout << "无解" << std::endl;
  } else {
    result[target] = 'T';
    for (auto pos = prev[target]; pos != start; pos = prev[pos])
      result[pos] = '2';
    result[start] = 'S';
    std::cout << result.toString2D() << std::endl;
  }
  return EXIT_SUCCESS;
}
