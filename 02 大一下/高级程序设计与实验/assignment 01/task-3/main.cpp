/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Smartly replaces a pattern in a text with a replacement.
 * The pattern is case-insensitive.
 * The replacement is case-sensitive.
 */

#include <format>

#include "console.h"
#include "hmwk.h"
#include "simpio.h"

int main() {
  std::string text = getLine("Enter text: ");
  std::string pattern = getLine("Enter pattern: ");
  std::string replacement = getLine("Enter replacement: ");

  std::string result = task3::smart_replace(text, pattern, replacement);

  std::cout << std::format("Result: {}", result) << std::endl;
  return 0;
}
