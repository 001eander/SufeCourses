/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1
 */

#include <cstdlib>
#include <sstream>

#include "console.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

int main() {
  auto input_str = getLine();
  auto input_stream = std::istringstream(input_str);
  auto input_vector = Vector<int>();
  auto exist_set = Set<int>();

  input_stream >> input_vector;
  if (input_stream.fail()) {
    std::cerr << "Invalid input format." << std::endl;
    return EXIT_FAILURE;
  }
  for (auto item : input_vector) exist_set.add(item);

  auto output_vector = Vector<int>();
  for (auto item : input_vector) {
    if (exist_set.contains(item)) {
      output_vector.add(item);
      exist_set.remove(item);
    }
  }

  std::cout << output_vector << std::endl;
  return EXIT_SUCCESS;
}
