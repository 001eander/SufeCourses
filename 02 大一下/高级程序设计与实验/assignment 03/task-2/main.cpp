/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 2: count
 */

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <format>
#include <fstream>
#include <string>

#include "console.h"
#include "simpio.h"
#include "vector.h"

struct Word_Info {
  std::string word;
  uint64_t count;
  bool operator<(const Word_Info& other) const {
    return (count == other.count) ? word < other.word : count > other.count;
  }
};

struct Char_Info {
  char ch;
  uint64_t count;
  bool operator<(const Char_Info& other) const {
    return (count == other.count) ? ch < other.ch : count > other.count;
  }
};

void update_info(Vector<Word_Info>& words, const std::string& word) {
  size_t pos = 0;
  while (pos < words.size() && words[pos].word != word) pos++;
  if (pos == words.size())
    words.add({word, 1ull});
  else
    words[pos].count++;
}

void update_info(Vector<Char_Info>& chars, char ch) {
  size_t pos = 0;
  while (pos < chars.size() && chars[pos].ch != ch) pos++;
  if (pos == chars.size())
    chars.add({ch, 1ull});
  else
    chars[pos].count++;
}

int main() {
  std::string filename = getLine("Enter file name: ");
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cout << "Can't open file " << filename << std::endl;
    return 1;
  }

  Vector<Word_Info> words;
  Vector<Char_Info> chars;

  char ch;
  std::string word;
  while (fin.get(ch)) {
    if (isalpha(ch)) {
      char lower_ch = tolower(ch);
      word += lower_ch;
      update_info(chars, lower_ch);
    } else {
      if (word.empty()) continue;
      update_info(words, word);
      word.clear();
    }
  }
  if (!word.empty()) update_info(words, word);

  words.sort();
  chars.sort();

  size_t max_len = 0;
  for (auto word_info : words)
    max_len = std::max(max_len, word_info.word.size());

  std::cout << "---=== Word frequency ===--- " << std::endl;
  for (auto word_info : words)
    std::cout << std::format("{:>{}} - {}", word_info.word, max_len + 2,
                             word_info.count)
              << std::endl;

  std::cout << "---=== Character frequency ===---" << std::endl;
  for (auto char_info : chars)
    std::cout << std::format("{:>{}} - {}", char_info.ch, max_len + 2,
                             char_info.count)
              << std::endl;

  return 0;
}
