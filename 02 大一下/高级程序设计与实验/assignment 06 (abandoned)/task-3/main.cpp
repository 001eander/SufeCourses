/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 3
 */

#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "map.h"
#include "simpio.h"
#include "strlib.h"

class Encoder {
 private:
  Map<char, char> encode_map;
  Map<char, char> decode_map;

 public:
  Encoder() {
    for (char ch = 'a'; ch <= 'z'; ++ch) {
      encode_map[ch] = ch;
      decode_map[ch] = ch;
    }
  }

  Encoder(const std::string& orig_str, const std::string& encoded_str) {
    for (size_t i = 0; i < orig_str.size(); ++i) {
      char orig_ch = orig_str[i];
      char encoded_ch = encoded_str[i];

      encode_map[toLowerCase(orig_ch)] = toLowerCase(encoded_ch);
      encode_map[toUpperCase(orig_ch)] = toUpperCase(encoded_ch);

      decode_map[toLowerCase(encoded_ch)] = toLowerCase(orig_ch);
      decode_map[toUpperCase(encoded_ch)] = toUpperCase(orig_ch);
    }
  }
  ~Encoder() = default;

  std::string encode(const std::string& str) {
    std::string result;
    for (auto ch : toLowerCase(str)) result += encode_map[ch];
    return result;
  }

  std::string decode(const std::string& str) {
    std::string result;
    for (auto ch : toLowerCase(str)) result += decode_map[ch];
    return result;
  }
};

std::string extract_pattern(const std::string& str) {
  auto lower_str = toLowerCase(str);
  std::string pattern;
  Map<char, char> record;
  char index = '0';
  for (auto ch : lower_str) {
    if (record.containsKey(ch)) {
      pattern += record[ch];
    } else {
      pattern += index++;
      record[ch] = index;
    }
  }
  return pattern;
}

Vector<std::string> DecodeIt(const std::string& encoded,
                             const std::string& word_list_path) {
  auto word_list_stream = std::ifstream(word_list_path);
  if (!word_list_stream.is_open()) {
    std::cerr << "Error: Could not open word list file." << std::endl;
    return {};
  }

  auto encoded_pattern = extract_pattern(encoded);
  Vector<std::string> decoded_words;
  std::string word;
  while (word_list_stream >> word) {
    auto word_pattern = extract_pattern(word);
    if (word_pattern == encoded_pattern) decoded_words.add(word);
  }
  return decoded_words;
}

int main() {
  auto original = getLine("Enter the original string: ");
  auto encoded = getLine("Enter the encoded string: ");
  Encoder encoder(original, encoded);

  auto to_encode = getLine("Enter the string to encode: ");
  std::cout << std::format("Encoded: {}", encoder.encode(to_encode))
            << std::endl;

  auto to_decode = getLine("Enter the string to decode: ");
  std::cout << std::format("Decoded: {}", encoder.decode(to_decode))
            << std::endl;

  auto word_list_path = getLine("Enter the word list file path: ");
  auto decoded_words = DecodeIt(to_decode, word_list_path);
  std::cout << "Decoded Results:" << std::endl;
  for (auto word : decoded_words) {
    std::cout << std::format(" - {}", word) << std::endl;
  }
  return EXIT_SUCCESS;
}
