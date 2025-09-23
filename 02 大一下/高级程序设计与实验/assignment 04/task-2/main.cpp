/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 2
 */

#include <cctype>
#include <cstdlib>
#include <format>
#include <fstream>
#include <sstream>

#include "console.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"

int main() {
  auto filename = getLine("Enter filename: ");
  auto fin = std::ifstream(filename);
  if (!fin.is_open()) {
    std::cerr << "Error: file not found" << std::endl;
    return EXIT_FAILURE;
  }

  auto lines = Vector<std::string>();
  for (std::string line; std::getline(fin, line);) lines.add(line);

  auto rows = lines.size();
  auto tmp_line = Vector<int>();
  auto sin = std::istringstream(lines[0]);
  for (int i; sin >> i;) tmp_line.add(i);
  auto cols = tmp_line.size();

  auto grid = Grid<int>(rows, cols);
  for (int i = 0; i < rows; i++) {
    auto sin = std::istringstream(lines[i]);
    for (int j = 0; j < cols; j++) sin >> grid[i][j];
  }
  std::cout << "Original grid:" << std::endl;
  std::cout << grid.toString2D() << std::endl;

  auto new_rows = getInteger("Enter number of rows: ");
  auto new_cols = getInteger("Enter number of columns: ");
  if (new_rows < 0 || new_cols < 0 || new_rows * new_cols != rows * cols) {
    std::cerr << "Error: invalid size" << std::endl;
    return EXIT_FAILURE;
  }

  auto new_grid = Grid<int>(new_rows, new_cols);
  auto i = 0, j = 0;
  for (auto item : grid) {
    new_grid[i][j] = item;
    j++;
    if (j == new_cols) {
      i++;
      j = 0;
    }
  }

  std::cout << "Resized grid:" << std::endl;
  std::cout << new_grid.toString2D() << std::endl;
  return EXIT_SUCCESS;
}
