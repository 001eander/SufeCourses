/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 2
 */

#include <format>
#include <fstream>

#include "console.h"
#include "simpio.h"
#include "strlib.h"

size_t smart_find(const std::string& str, const std::string& pattern,
                  size_t start = 0, bool ignore_case = false) {
  if (ignore_case) return toLowerCase(str).find(toLowerCase(pattern), start);
  return str.find(pattern, start);
}

size_t simple_replace_all(std::string& str, const std::string& pattern,
                          const std::string& replacement, size_t line_count,
                          bool ignore_case = false) {
  size_t pos = 0, count = 0;
  while ((pos = smart_find(str, pattern, pos, ignore_case)) !=
         std::string::npos) {
    auto before_pos = (pos > 5 ? pos - 5 : 0);
    std::string before = str.substr(before_pos, pos - before_pos);
    std::string replaced = str.substr(pos, pattern.length());
    std::string after = str.substr(pos + pattern.length(), 5);

    std::cout << std::format(
                     "REPLACE {}-{}: {}{}[{}->{}]{}{}", line_count, pos,
                     (before_pos == 0 ? "" : "..."), before, replaced,
                     replacement, after,
                     (pos + pattern.length() + 5 < str.length() ? "..." : ""))
              << std::endl;

    str.replace(pos, pattern.length(), replacement);
    pos += replacement.length();
    count++;
  }
  return count;
}

int main() {
  std::string in_file_name = getLine("Enter input file name: ");
  std::string pattern = getLine("Enter pattern: ");
  std::string replacement = getLine("Enter replacement: ");
  bool ignore_case = (getInteger("Ignore case? (0 - no, 1 - yes): ") == 1);
  std::string out_file_name = getLine("Enter output file name: ");

  std::ifstream in_file(in_file_name);
  if (!in_file) {
    std::cerr << "Error: Can't open file " << in_file_name << std::endl;
    return 1;
  }
  std::ofstream out_file(out_file_name);
  if (!out_file) {
    std::cerr << "Error: Can't open file " << out_file_name << std::endl;
    return 1;
  }

  size_t line_count = 0, replaced_count = 0;
  std::string line;
  while (in_file) {
    line_count++;
    std::getline(in_file, line);
    replaced_count +=
        simple_replace_all(line, pattern, replacement, line_count, ignore_case);
    out_file << line << std::endl;
  }
  std::cout << std::format("All done! {} {} replaced in total.", replaced_count,
                           (replaced_count == 1 ? "occurrence was"
                                                : "occurrences were"))
            << std::endl;
  return 0;
}
