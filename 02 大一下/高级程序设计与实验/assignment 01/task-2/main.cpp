/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Count the number of characters in your text and then,  print those characters
 * acording to their frequency descendingly.
 */

#include "console.h"
#include "hmwk.h"
#include "simpio.h"

int main() {
  std::string text = getLine("Please enter your text:\n");

  auto char_count_vec = task2::count_char(text);

  for (const auto& [ch, count] : char_count_vec)
    std::cout << std::format("'{}'({:3}): {}\n", ch, static_cast<int>(ch),
                             count);
  return 0;
}
