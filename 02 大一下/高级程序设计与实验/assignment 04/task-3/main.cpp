/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 3
 */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "grid.h"
#include "simpio.h"

int main() {
  auto filename = getLine("Enter filename: ");
  auto fin = std::ifstream(filename);
  if (!fin.is_open()) {
    std::cout << "Error: file not found" << std::endl;
    return EXIT_FAILURE;
  }

  Grid<int> grid(9, 9);
  for (auto& item : grid) fin >> item;

  for (auto row = 0; row < 9; ++row) {
    bool exist[1 + 9] = {false};
    for (auto col = 0; col < 9; ++col) exist[grid[row][col]] = true;
    for (auto i = 1; i <= 9; ++i) {
      if (!exist[i]) {
        std::cout << "Error: row " << row + 1 << " is missing " << i
                  << std::endl;
        return EXIT_SUCCESS;
      }
    }
  }

  for (auto col = 0; col < 9; ++col) {
    bool exist[1 + 9] = {false};
    for (auto row = 0; row < 9; ++row) exist[grid[row][col]] = true;
    for (auto i = 1; i <= 9; ++i) {
      if (!exist[i]) {
        std::cout << "Error: column " << col + 1 << " is missing " << i
                  << std::endl;
        return EXIT_SUCCESS;
      }
    }
  }

  for (auto row = 0; row < 9; row += 3) {
    for (auto col = 0; col < 9; col += 3) {
      auto range = GridLocationRange(row, col, row + 2, col + 2);
      bool exist[1 + 9] = {false};
      for (auto loc : range) exist[grid[loc]] = true;
      for (auto i = 1; i <= 9; ++i) {
        if (!exist[i]) {
          std::cout << "Error: 3x3 square at (" << row + 1 << ", " << col + 1
                    << ") is missing " << i << std::endl;
          return EXIT_SUCCESS;
        }
      }
    }
  }

  std::cout << "The puzzle is correct." << std::endl;
  return EXIT_SUCCESS;
}
