/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task-3
 */

#include <algorithm>
#include <cctype>
#include <format>
#include <fstream>
#include <map>
#include <vector>

#include "console.h"
#include "simpio.h"
#include "strlib.h"

struct Word_Info {
  size_t occurences;
  std::vector<std::pair<size_t, size_t>> positions;
};

std::vector<std::pair<std::string, size_t>> split(const std::string& str) {
  std::vector<std::pair<std::string, size_t>> result;
  std::string word;
  for (char ch : str) {
    if (!isalpha(ch)) {
      if (!word.empty()) {
        result.emplace_back(toLowerCase(word), str.find(word));
        word.clear();
      }
    } else {
      word += ch;
    }
  }
  if (!word.empty()) result.emplace_back(toLowerCase(word), str.find(word));
  return result;
}

void update(std::map<std::string, Word_Info>& words,
            const std::vector<std::pair<std::string, size_t>>& line,
            size_t line_cnt) {
  for (auto [word, pos] : line) {
    if (words.find(word) == words.end()) {
      words[word] = {1, {{line_cnt, pos}}};
    } else {
      words[word].occurences++;
      words[word].positions.push_back({line_cnt, pos});
    }
  }
}

int main() {
  std::string in_file_name = getLine("Enter input file name: ");
  std::ifstream in_file(in_file_name);
  if (!in_file.is_open()) {
    std::cerr << "Can't open file: " << in_file_name << std::endl;
    return 1;
  }

  std::map<std::string, Word_Info> words;
  std::string line;
  size_t line_cnt = 0, word_cnt = 0, none_blacnk_cnt = 0, char_cnt = 0;
  while (std::getline(in_file, line)) {
    line_cnt++;
    auto words_in_line = split(line);
    word_cnt += words_in_line.size();
    none_blacnk_cnt += std::count_if(line.begin(), line.end(),
                                     [](char ch) { return !isblank(ch); });
    char_cnt += line.size();

    update(words, words_in_line, line_cnt);
  }
  std::cout << std::format(
      "Lines: {}\nWords: {}\nCharacters: {}\nNone blank "
      "characters: {}\n",
      line_cnt, word_cnt, char_cnt, none_blacnk_cnt);
  std::cout << "Words info:\n";

  std::vector<std::pair<std::string, Word_Info>> words_vec;
  for (const auto& [word, info] : words) words_vec.push_back({word, info});
  std::sort(words_vec.begin(), words_vec.end(),
            [](const auto& lhs, const auto& rhs) {
              return lhs.second.occurences > rhs.second.occurences;
            });

  for (const auto& [word, info] : words_vec) {
    std::cout << std::format("{}({}): ", word, info.occurences);
    for (const auto& [line, pos] : info.positions)
      std::cout << std::format("({}, {}) ", line, pos);
    std::cout << std::endl;
  }
  return 0;
}
