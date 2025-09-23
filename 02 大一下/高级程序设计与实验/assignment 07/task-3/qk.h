#ifndef QK_H
#define QK_H

#include <algorithm>

#include "vector.h"

template <typename ValueType>
Vector<ValueType> qsort_(const Vector<ValueType>& a) {
  if (a.size() <= 1) return a;
  auto pivot = a[a.size() / 2];
  Vector<ValueType> less, equal, greater;
  for (auto item : a)
    if (item < pivot)
      less += item;
    else if (item == pivot)
      equal += item;
    else
      greater += item;
  return qsort_(less) + equal + qsort_(greater);
}

template <typename ValueType>
ValueType plain_kth_(const Vector<ValueType>& a, int k) {
  if (k < 0 || k >= a.size()) throw std::out_of_range("Index out of range");
  return qsort_(a)[k];
}

template <typename ValueType>
ValueType q_kth_(const Vector<ValueType>& a, int k) {
  if (k < 0 || k >= a.size()) throw std::out_of_range("Index out of range");
  auto pivot = a[a.size() / 2];
  Vector<ValueType> less, equal, greater;
  for (auto item : a)
    if (item < pivot)
      less += item;
    else if (item == pivot)
      equal += item;
    else
      greater += item;
  if (k < less.size()) return q_kth_(less, k);
  if (k < less.size() + equal.size()) return pivot;
  return q_kth_(greater, k - less.size() - equal.size());
}

template <typename ValueType>
Vector<ValueType> generate(int n = 0) {
  srand(time(nullptr));
  Vector<ValueType> a;
  if (n == 0) n = rand() % 1000 + 1;
  for (int i = 0; i < n; ++i) a += rand() % 100;
  return a;
}

template <typename ValueType>
bool test_kth_(int times = 1000) {
  for (int i = 0; i < times; ++i) {
    Vector<ValueType> a = generate<ValueType>();
    int k = rand() % a.size();
    auto plain = plain_kth_(a, k);
    auto q = q_kth_(a, k);
    if (plain != q) {
      std::cout << "Error: " << plain << " != " << q << std::endl;
      std::cout << "Index: " << k << std::endl;
      std::cout << "Array: ";
      std::cout << a << std::endl;
      return false;
    }
  }
  return true;
}

#endif  // QK_H
