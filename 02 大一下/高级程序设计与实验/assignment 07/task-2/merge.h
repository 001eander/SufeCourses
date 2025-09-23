#ifndef MERGE_H
#define MERGE_H

#include <algorithm>

#include "vector.h"

int plain_reverse_pair_cnt(const Vector<int>& vec) {
  int cnt = 0;
  for (int i = 0; i < vec.size(); ++i)
    for (int j = i + 1; j < vec.size(); ++j)
      if (vec[i] > vec[j]) ++cnt;
  return cnt;
}

Vector<int> merge_sort(const Vector<int>& vec) {
  if (vec.size() <= 1) return vec;
  int mid = vec.size() / 2;
  auto left = merge_sort(vec.subList(0, mid));
  auto right = merge_sort(vec.subList(mid, vec.size() - mid));
  Vector<int> merged(left.size() + right.size());
  int i = 0, j = 0, k = 0;
  while (i < left.size() && j < right.size())
    if (left[i] <= right[j])
      merged[k++] = left[i++];
    else
      merged[k++] = right[j++];
  return merged;
}

std::pair<int, Vector<int>> merge_reverse_pair_cnt(const Vector<int>& vec) {
  if (vec.size() <= 1) return {0, vec};
  int mid = vec.size() / 2;
  auto [left_cnt, left_vec] = merge_reverse_pair_cnt(vec.subList(0, mid));
  auto [right_cnt, right_vec] =
      merge_reverse_pair_cnt(vec.subList(mid, vec.size() - mid));
  int cnt = left_cnt + right_cnt;
  Vector<int> merged(left_vec.size() + right_vec.size());
  int i = 0, j = 0, k = 0;
  while (i < left_vec.size() && j < right_vec.size()) {
    if (left_vec[i] <= right_vec[j]) {
      merged[k++] = left_vec[i++];
    } else {
      merged[k++] = right_vec[j++];
      cnt += left_vec.size() - i;
    }
  }
  while (i < left_vec.size()) merged[k++] = left_vec[i++];
  while (j < right_vec.size()) merged[k++] = right_vec[j++];
  return {cnt, merged};
}

Vector<int> generate_vector(int size) {
  srand(time(nullptr));
  Vector<int> vec(size);
  for (int i = 0; i < size; ++i) vec[i] = rand() % size;
  return vec;
}

Vector<int> test_reverse_pair_cnt(int times) {
  while (times--) {
    int size = rand() % 1000 + 1;
    Vector<int> vec = generate_vector(size);
    int plain_cnt = plain_reverse_pair_cnt(vec);
    auto [merge_cnt, _] = merge_reverse_pair_cnt(vec);
    if (plain_cnt != merge_cnt) {
      std::cout << "Error: " << plain_cnt << " " << merge_cnt << std::endl;
      return vec;
    }
  }
  return Vector<int>();
}

#endif  // MERGE_H
