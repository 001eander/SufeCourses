/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1 in FP
 */

#include <algorithm>
#include <format>
#include <fstream>
#include <numeric>
#include <regex>
#include <vector>

#include "console.h"
#include "simpio.h"
#include "strlib.h"

template <typename Type>
std::vector<Type> readVector(std::istream& is) {
  std::vector<Type> vector;
  Type value;
  while (is >> value) vector.push_back(value);
  return vector;
}

double reverse_number_to_double(const std::string& reverse_number) {
  std::string number = reverse_number;
  std::reverse(number.begin(), number.end());
  auto p = number.find('#');
  if (p != std::string::npos) number.replace(p, 1, ".");
  return stringToDouble(number);
}

int main() {
  std::string filename = getLine("Enter filename: ");
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Can't open file " << filename << std::endl;
    return 1;
  }

  auto reverse_numbers = readVector<std::string>(fin);

  auto numbers = std::vector<std::string>();
  std::regex reverse_number_pattern("^\\d+(\\#\\d+)?-?$");
  std::copy_if(reverse_numbers.begin(), reverse_numbers.end(),
               std::back_inserter(numbers),
               [reverse_number_pattern](const std::string& reverse_number) {
                 return std::regex_match(reverse_number,
                                         reverse_number_pattern);
               });

  std::vector<double> numbers_double;
  std::transform(numbers.begin(), numbers.end(),
                 std::back_inserter(numbers_double), reverse_number_to_double);

  auto sum = std::accumulate(numbers_double.begin(), numbers_double.end(), 0.0);

  std::cout << std::format("Sum of numbers: {:.5f}", sum) << std::endl;
  return 0;
}
