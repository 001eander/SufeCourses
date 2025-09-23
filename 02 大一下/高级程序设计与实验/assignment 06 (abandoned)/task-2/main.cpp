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
#include <sstream>

#include "console.h"
#include "grid.h"
#include "set.h"
#include "simpio.h"

bool is_valid_sudoku(const Grid<int> &grid) {
  // Check if the grid is a 9x9 grid
  if (grid.numRows() != 9 || grid.numCols() != 9) return false;

  // Check if the grid contains only valid numbers (0-9)
  for (size_t row = 0; row < 9; ++row)
    for (size_t col = 0; col < 9; ++col)
      if (!(1 <= grid[row][col] && grid[row][col] <= 9)) return false;

  // According to the problem statement, we use Set<int> to track seen numbers
  // in the current row, column, or subgrid.
  Set<int> seen;

  // Check rows
  for (size_t row = 0; row < 9; ++row) {
    for (size_t col = 0; col < 9; ++col) {
      if (seen.contains(grid[row][col])) return false;
      seen.add(grid[row][col]);
    }
  }
  seen.clear();

  // Check columns
  for (size_t col = 0; col < 9; ++col) {
    for (size_t row = 0; row < 9; ++row) {
      if (seen.contains(grid[row][col])) return false;
      seen.add(grid[row][col]);
    }
  }
  seen.clear();

  // Check 3x3 subgrids
  for (size_t subgrid_id = 0; subgrid_id < 9; ++subgrid_id) {
    int start_row = (subgrid_id / 3) * 3, start_col = (subgrid_id % 3) * 3;
    for (auto loc : GridLocationRange({start_row, start_col},
                                      {start_row + 3, start_col + 3})) {
      if (seen.contains(grid[loc])) return false;
      seen.add(grid[loc]);
    }
  }

  return true;
}

int main() {
  auto input_str = getLine();
  auto input_stream = std::istringstream(input_str);
  Grid<int> sudoku;
  input_stream >> sudoku;
  if (input_stream.fail()) {
    std::cerr << "Invalid input format." << std::endl;
    return EXIT_FAILURE;
  }

  if (!is_valid_sudoku(sudoku)) {
    std::cout << "NO" << std::endl;
    return EXIT_SUCCESS;
  }
  std::cout << "YES" << std::endl;

  return EXIT_SUCCESS;
}
