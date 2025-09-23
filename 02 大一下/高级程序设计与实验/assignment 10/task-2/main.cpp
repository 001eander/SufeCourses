/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Task 2
 */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <fstream>

#include "console.h"
#include "hashmap.h"
#include "priorityqueue.h"
#include "simpio.h"
#include "vector.h"

using std::cout;
using std::endl;
using std::string;

bool is_connected(string w1, string w2) {
  if ((w2.size() - w1.size() > 1) || (w1.size() - w2.size() > 1)) return false;
  if (w1.size() > w2.size()) std::swap(w1, w2);

  if (w1.size() == w2.size()) {
    for (char& letter : w1) {
      char backup = letter;
      for (char ch : "abcdefghijklmnopqrstuvwxyz") {
        letter = ch;
        if (w1 == w2) return true;
      }
      letter = backup;
    }
    for (size_t i = 0; i < w1.size(); ++i) {
      for (size_t j = i + 1; j < w1.size(); ++j) {
        std::swap(w1[i], w1[j]);
        if (w1 == w2) return true;
        std::swap(w1[i], w1[j]);
      }
    }
  } else {
    for (char ch : "abcdefghijklmnopqrstuvwxyz") {
      for (size_t i = 0; i < w1.size(); ++i) {
        auto nw = w1;
        nw.insert(i, 1, ch);
        if (nw == w2) return true;
      }
    }
  }

  return false;
}

HashMap<string, Vector<string>> mem{};

Vector<string> get_connected_words(string word, const Vector<string>& words) {
  if (mem.containsKey(word)) return mem[word];

  Vector<string> res{};
  for (string w : words)
    if (is_connected(word, w)) res += w;

  mem[word] = res;
  return res;
}

void get_paths_helper(string word, string target, Vector<string> path,
                      Vector<Vector<string>>& paths,
                      HashMap<string, bool>& visited,
                      const Vector<string>& words) {
  if (!paths.isEmpty() && (path.size() > paths[0].size())) return;

  if (word == target) {
    if (!paths.isEmpty() && (path.size() < paths[0].size())) paths.clear();
    paths += path;
    return;
  }

  if (visited[word]) return;
  visited[word] = true;
  for (string w : get_connected_words(word, words))
    get_paths_helper(w, target, path + w, paths, visited, words);
  visited[word] = false;
}

Vector<Vector<string>> get_paths(string w1, string w2,
                                 const Vector<string>& words) {
  Vector<Vector<string>> paths{};
  HashMap<string, bool> visited{};
  for (string word : words) visited[word] = false;
  get_paths_helper(w1, w2, {w1}, paths, visited, words);
  return paths;
}

int main() {
  std::ifstream fin{"./EnglishWords.txt"};
  Vector<string> words;
  while (fin) {
    string word{};
    fin >> word;
    if (word.size() > 0) words += word;
  }

  string w1 = getLine("Enter the first word: ");
  string w2 = getLine("Enter the second word: ");

  auto paths = get_paths(w1, w2, words);

  for (auto path : paths) {
    for (size_t i = 0; i < path.size(); ++i) {
      cout << path[i];
      if (i + 1 != path.size())
        cout << " -> ";
      else
        cout << endl;
    }
  }

  return EXIT_SUCCESS;
}
