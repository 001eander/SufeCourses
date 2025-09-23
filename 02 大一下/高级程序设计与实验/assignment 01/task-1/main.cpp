/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Remove unnecessary spaces in your text.
 */

#include "console.h"
#include "hmwk.h"
#include "simpio.h"

int main() {
  std::string text = getLine("Please enter your text:\n");
  std::cout << "Here is your text without unnecessary spaces:" << std::endl;
  std::cout << task1::clean_space(text) << std::endl;
  return 0;
}
