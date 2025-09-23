/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1: Bracket Matching
 *
 * To avoid comlexity, we will only consider simple cpp files that don't contain
 * brackets in strings or comments.
 *
 * The program will read a file and check if all brackets are matched with a
 * stack.
 */

#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "simpio.h"
#include "stack.h"
#include "strlib.h"

inline bool is_bracket(char ch) { return stringContains("()[]{}", ch); }

inline bool is_left(char ch) { return stringContains("([{", ch); }
inline bool is_right(char ch) { return stringContains(")]}", ch); }

inline bool is_matching(char left, char right) {
  return (left == '(' && right == ')') || (left == '[' && right == ']') ||
         (left == '{' && right == '}');
}

int main() {
  const std::string filename = getLine("Enter file name: ");
  auto fin = std::ifstream(filename);
  if (!fin) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    return EXIT_FAILURE;
  }

  auto stk = Stack<char>();
  auto line = std::string();
  auto line_number = 0ull;
  auto column_number = 0ull;

  while (std::getline(fin, line)) {
    ++line_number;
    column_number = 0ull;

    for (const auto& ch : line) {
      ++column_number;

      if (!is_bracket(ch)) {
        continue;
      }

      if (is_left(ch)) {
        stk.push(ch);
        continue;
      }

      if (is_right(ch)) {
        if (stk.isEmpty()) {
          std::cout << std::format("Unmatched {} at line {}, column {}", ch,
                                   line_number, column_number);
          return EXIT_FAILURE;
        }

        const auto left = stk.pop();
        if (!is_matching(left, ch)) {
          std::cout << std::format("Unmatched {} at line {}, column {}", ch,
                                   line_number, column_number);
          return EXIT_FAILURE;
        }
      }
    }
  }
  if (!stk.isEmpty()) {
    std::cout << std::format("Unmatched {} at line {}, column {}", stk.pop(),
                             line_number, column_number);
    return EXIT_FAILURE;
  }

  std::cout << -1 << std::endl;
  std::cout << "All brackets matched!" << std::endl;
  return EXIT_SUCCESS;
}
