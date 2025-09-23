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
#include "simpio.h"

std::string reverse(const std::string& str) {
  if (str.empty()) return str;
  return reverse(str.substr(1, str.size() - 1)) + str[0];
}

bool palindrome(const std::string& str) {
  if (str.size() <= 1) return true;
  if (str[0] != str.back()) return false;
  return palindrome(str.substr(1, str.size() - 2));
}

int main() {
  std::cout << "Hello world!" << std::endl;
  std::cout << reverse("Hello world!") << std::endl;
  std::cout << std::format("Is \"{}\" a palindrome? {}", "racecar",
                           palindrome("racecar") ? "yes" : "no")
            << std::endl;
  std::cout << std::format("Is \"{}\" a palindrome? {}", "hello",
                           palindrome("hello") ? "yes" : "no")
            << std::endl;
  return EXIT_SUCCESS;
}
