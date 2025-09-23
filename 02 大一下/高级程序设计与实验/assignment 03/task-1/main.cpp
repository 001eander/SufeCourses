/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 1: judge
 */
#include <format>

#include "console.h"
#include "simpio.h"
#include "vector.h"

int main() {
  Vector<int> scores;
  std::cout << "Enter the scores in the form of {score-1, score-2, ...}: ";
  if (!(std::cin >> scores)) {
    std::cerr << "Invalid input. " << std::endl;
    return -1;
  }

  scores.sort();
  auto len = scores.size();
  scores = scores.subList(1, len - 2);
  len -= 2;

  int32_t sum = 0;
  for (auto score : scores) sum += score;
  auto mean = 1.0 * sum / len;
  double ssd = 0;
  for (auto score : scores) ssd += (score - mean) * (score - mean);
  auto variance = ssd / len;

  std::cout << "After removing the lowest and highest scores, ";
  std::cout << std::format("the mean is {:.1f} and the variance is {:.1f}",
                           mean, variance)
            << std::endl;
  return 0;
}
