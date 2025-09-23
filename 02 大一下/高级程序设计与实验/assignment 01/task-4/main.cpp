/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Translate your text to a new language.
 */

#include "console.h"
#include "hmwk.h"
#include "simpio.h"

int main() {
  std::string text = getLine("Enter text: ");
  std::cout << "Translation: " << task4::translate(text) << std::endl;
  return 0;
}
