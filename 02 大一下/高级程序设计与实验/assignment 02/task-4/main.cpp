/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task-4
 */

#include <fstream>
#include <regex>
#include <vector>

#include "console.h"
#include "simpio.h"
#include "strlib.h"

std::string protect(const std::string &str) {
  bool in_quotes = false;
  std::string protected_str = "";
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '"') in_quotes = !in_quotes;
    protected_str += (in_quotes && str[i] == '/' ? '@' : str[i]);
  }
  return protected_str;
}

std::string deprotect(const std::string &protected_str) {
  bool in_quotes = false;
  std::string str = "";
  for (size_t i = 0; i < protected_str.length(); ++i) {
    if (protected_str[i] == '"') in_quotes = !in_quotes;
    str += (in_quotes && protected_str[i] == '@' ? '/' : protected_str[i]);
  }

  return str;
}

int main() {
  std::string filename = getLine("Enter the file name: ");
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Can't open " << filename << std::endl;
    return 1;
  }

  std::string _ = "Noise: //";
  // test

  std::string line, program;
  while (getline(file, line)) program += line + "\n";

  auto protected_program = protect(program) + "\n";

  std::string result = "";
  for (size_t i = 0; i < protected_program.length(); ++i) {
    if (protected_program[i] == '/' && i + 1 < protected_program.length() &&
        protected_program[i + 1] == '/')
      i = protected_program.find('\n', i) + 1;

    if (protected_program[i] == '/' && i + 1 < protected_program.length() &&
        protected_program[i + 1] == '*')
      i = protected_program.find("*/", i) + 2;

    if (i < protected_program.length()) result += protected_program[i];
  }

  std::vector<std::string> lines;
  for (size_t i = 0; i < result.length(); ++i) {
    if (result[i] == '\n') {
      lines.push_back(trimEnd(result.substr(0, i)));
      result = result.substr(i + 1);
      i = 0;
    }
  }

  result = "";
  for (size_t i = 0; i < lines.size(); ++i) {
    if (lines[i].empty()) continue;
    result += lines[i] + "\n";
  }

  std::string output_filename = filename.substr(0, filename.find_last_of('.')) +
                                "_cleaned" +
                                filename.substr(filename.find_last_of('.'));
  std::ofstream out(output_filename);
  if (!out.is_open()) {
    std::cout << "Can't create output file " << output_filename << std::endl;
    return 1;
  }
  out << deprotect(result);
  std::cout << "The cleaned version of the program has been saved to "
            << output_filename << std::endl;
  return 0;
}
