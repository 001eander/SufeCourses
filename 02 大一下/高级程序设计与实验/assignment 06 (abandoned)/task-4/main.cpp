/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 4
 */

#include <cstdint>
#include <cstdlib>
#include <format>

#include "console.h"
#include "map.h"
#include "set.h"
#include "simpio.h"

int main() {
  auto num_of_students = getInteger("Enter number of students: ");
  Map<int, Set<std::string>> students;
  for (size_t i = 0; i < num_of_students; i++) {
    auto student_name = std::string();
    auto student_grade = 0;
    std::cin >> student_name >> student_grade;

    students[-student_grade].add(student_name);
  }

  for (auto neg_grade : students) {
    auto student_name_set = students[neg_grade];
    auto grade = -neg_grade;
    for (auto student_name : student_name_set)
      std::cout << std::format("{}: {}", student_name, grade) << std::endl;
  }
  return EXIT_SUCCESS;
}
