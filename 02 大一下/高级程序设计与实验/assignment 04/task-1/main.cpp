/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1
 */

#include <format>

#include "console.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"

int main() {
  std::cout << "Please enter the number of rows and columns: ";
  auto rows = 0, cols = 0;
  std::cin >> rows >> cols;

  std::string line;
  Grid<bool> grid(rows, cols);
  for (auto i = 0; i < rows; ++i) {
    std::cin >> line;
    for (auto j = 0; j < cols; ++j) grid[i][j] = (line[j] == 'T');
  }

  for (auto i = 0; i < rows; ++i) {
    for (auto j = 0; j < cols; ++j) {
      auto cnt = 0;
      for (auto dx = -1; dx <= 1; ++dx) {
        for (auto dy = -1; dy <= 1; ++dy) {
          auto x = i + dx, y = j + dy;
          if (grid.inBounds(x, y) && grid[x][y]) ++cnt;
        }
      }
      std::cout << " " << cnt;
    }
    std::cout << std::endl;
  }
  return 0;
}
