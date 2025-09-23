#ifndef HMWK_H
#define HMWK_H

#include <algorithm>
#include <cctype>
#include <format>
#include <string>
#include <unordered_map>
#include <vector>

#include "strlib.h"

namespace task1 {
std::string clean_space(const std::string &text) {
  std::string trimed_text = trim(text);

  // manully insert space after punctuation
  for (size_t i = 0; i < trimed_text.size(); ++i)
    if (ispunct(trimed_text[i])) trimed_text.insert(i + 1, " ");

  std::string clean_text = "";
  for (auto i = trimed_text.begin(); i != trimed_text.end(); ++i) {
    if (isspace(*i)) {
      auto next = std::find_if(i, trimed_text.end(),
                               [](auto ch) { return !isspace(ch); });
      // Because of trim(), we don't need to check if next is trimed_text.end()
      if (!ispunct(*next)) clean_text += ' ';
      i = next - 1;
    } else
      clean_text += *i;
  }
  return clean_text;
}
}  // namespace task1

namespace task4 {
bool is_vowel(char ch) { return stringContains("aeiouAEIOU", ch); }

std::string translate_word(const std::string &word) {
  if (word.empty()) return word;
  if (std::none_of(word.begin(), word.end(), is_vowel)) return word;
  if (is_vowel(word[0])) return word + "vae";

  auto pos = std::find_if(word.begin(), word.end(), is_vowel);
  return std::string(pos, word.end()) + std::string(word.begin(), pos) + "ae";
}

std::string translate(const std::string &text) {
  std::string result;
  std::string word;
  for (char ch : text) {
    if (isalpha(ch)) {
      word += ch;
    } else {
      if (!word.empty()) {
        result += translate_word(word);
        word.clear();
      }
      result += ch;
    }
  }
  if (!word.empty()) result += translate_word(word);
  return result;
}
}  // namespace task4

namespace task3 {
std::vector<size_t> kmp_search(const std::string &text,
                               const std::string &pattern) {
  std::vector<size_t> result;
  if (pattern.empty()) return result;

  std::vector<size_t> lps(pattern.size(), 0);
  size_t j = 0;

  // Preprocess the pattern (calculate lps array)
  for (size_t i = 1; i < pattern.size(); ++i) {
    if (pattern[i] == pattern[j]) {
      lps[i] = ++j;
    } else {
      if (j != 0) {
        j = lps[j - 1];
        --i;
      } else {
        lps[i] = 0;
      }
    }
  }

  // Search the pattern in the text
  size_t i = 0;
  j = 0;
  while (i < text.size()) {
    if (pattern[j] == text[i]) {
      ++i;
      ++j;
    }

    if (j == pattern.size()) {
      result.push_back(i - j);
      j = lps[j - 1];
    } else if (i < text.size() && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }

  return result;
}

std::string smart_replace(const std::string &text, const std::string &pattern,
                          const std::string &replacement) {
  std::string result = text;
  for (std::vector<size_t> matches =
           kmp_search(toLowerCase(text), toLowerCase(pattern));
       matches.size() != 0;
       matches = kmp_search(toLowerCase(result), toLowerCase(pattern))) {
    size_t offset = 0;
    for (size_t i = 0; i < matches.size(); ++i) {
      result.replace(matches[i] + offset, pattern.size(), replacement);
      offset += replacement.size() - pattern.size();
    }
  }
  return result;
}
}  // namespace task3

namespace task2 {
std::vector<std::pair<char, size_t>> count_char(const std::string &text) {
  std::unordered_map<char, size_t> char_count;
  for (auto ch : text) char_count[ch]++;
  std::vector<std::pair<char, size_t>> char_count_vec(char_count.begin(),
                                                      char_count.end());
  std::sort(
      char_count_vec.begin(), char_count_vec.end(),
      [](const auto &a, const auto &b) {
        return (a.second != b.second ? a.second > b.second : a.first < b.first);
      });
  return char_count_vec;
}
}  // namespace task2

#endif  // HMWK_H
