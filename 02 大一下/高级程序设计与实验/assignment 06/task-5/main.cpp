/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 5
 */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "map.h"
#include "set.h"
#include "simpio.h"

struct Course {
  std::string name;
  int point, grade;

  bool operator<(const Course& oth) const {
    return std::tie(oth.grade, oth.name, oth.point) <
           std::tie(grade, name, point);
  }
};

double get_score(Course course, Map<std::pair<int, int>, double>& gpa_map) {
  for (auto [left, right] : gpa_map)
    if (left <= course.grade && course.grade <= right)
      return gpa_map[{left, right}];
  return -1.0;
}

int main() {
  auto gpa_stream = std::ifstream("gpa.txt");
  if (!gpa_stream) {
    std::cerr << "Error: could not open gpa.txt" << std::endl;
    return EXIT_FAILURE;
  }

  int left, right;
  double grade;
  auto gpa_map = Map<std::pair<int, int>, double>();
  while (gpa_stream >> left >> right >> grade) gpa_map[{left, right}] = grade;

  auto grade_map = Map<double, Set<Course>>();

  auto grade_stream = std::ifstream("grade.txt");
  if (!grade_stream) {
    std::cerr << "Error: could not open grade.txt" << std::endl;
    return EXIT_FAILURE;
  }

  Course course;
  while (grade_stream >> course.name >> course.point >> course.grade) {
    auto score = get_score(course, gpa_map);
    if (score == -1.0) {
      std::cerr << "Error: invalid grade for " << course.name << std::endl;
      return EXIT_FAILURE;
    }

    grade_map[-score].add(course);
  }

  for (auto neg_score : grade_map) {
    std::cout << std::format("{:.2f}", -neg_score) << " -- ";
    for (auto course : grade_map[neg_score]) {
      std::cout << std::format("{}({}, {})", course.name, course.point,
                               course.grade)
                << " ";
    }
    std::cout << std::endl;
  }
  return EXIT_SUCCESS;
}
