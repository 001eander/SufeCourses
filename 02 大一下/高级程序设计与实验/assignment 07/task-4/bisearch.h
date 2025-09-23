#ifndef BISEARCH_H
#define BISEARCH_H

#include <algorithm>

#include "vector.h"

bool is_sorted(const Vector<int>& seq) {
  for (size_t i = 1; i < seq.size(); ++i)
    if (seq[i] < seq[i - 1]) return false;
  return true;
}

template <typename ValueType>
size_t plain_find_(const Vector<ValueType> seq, ValueType value) {
  if (!is_sorted(seq))
    throw std::invalid_argument("The sequence is not sorted.");

  if (seq[0] >= value) return seq.size();

  for (size_t i = 1; i < seq.size(); ++i)
    if (seq[i] >= value) return i - 1;

  return seq.size() - 1;
}

template <typename ValueType>
size_t q_find_(const Vector<ValueType>& seq, ValueType value, size_t left,
               size_t right) {
  // std::cout << "left: " << left << "; " << "right: " << right << std::endl;
  // std::cout << "value: " << value << "; " << seq << std::endl;
  if (left >= right) return right;
  size_t mid = left + (right - left + 1) / 2;
  if (value <= seq[mid]) return q_find_(seq, value, left, mid - 1);
  return q_find_(seq, value, mid, right);
}

template <typename ValueType>
size_t q_find_(const Vector<ValueType>& seq, ValueType value) {
  if (!is_sorted(seq))
    throw std::invalid_argument("The sequence is not sorted.");
  if (seq[0] >= value) return seq.size();
  return q_find_(seq, value, 0, seq.size() - 1);
}

template <typename ValueType>
Vector<ValueType> generate(int n = 0) {
  srand(time(nullptr));
  if (n == 0) n = rand() % 1000 + 1;
  Vector<ValueType> seq;
  while (n--) seq += rand() % 1000 + 1;
  std::sort(seq.begin(), seq.end());
  return seq;
}

template <typename ValueType>
bool test_find_(size_t times = 1000) {
  srand(time(nullptr));
  while (times--) {
    Vector<ValueType> seq = generate<ValueType>();
    ValueType value = rand() % 1000 + 1;
    size_t plain_index = plain_find_(seq, value);
    size_t q_index = q_find_(seq, value);
    if (plain_index != q_index) {
      std::cout << "plain_index: " << plain_index << std::endl;
      std::cout << "q_index: " << q_index << std::endl;
      std::cout << "value: " << value << std::endl;
      for (size_t i = 0; i < seq.size(); ++i)
        std::cout << i << ": " << seq[i] << std::endl;
      return false;
    }
  }
  return true;
}

#endif  // BISEARCH_H
