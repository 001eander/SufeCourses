#include <ctime>
#include <format>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
bool is_prime(T x) {
  if (x < 2) return false;
  if (x == 2) return true;
  if (x % 2 == 0) return false;
  for (T i = 3; i * i <= x; i += 2)
    if (x % i == 0) return false;
  return true;
}

template <typename T1, typename T2>
T1 expmod(T1 base, T2 exp, T1 m) {
  if (exp == 0) return 1;
  if (exp % 2 == 0) {
    auto tmp = expmod(base, exp / 2, m);
    return tmp * tmp % m;
  };
  return base * expmod(base, exp - 1, m) % m;
}

template <typename T>
bool is_prime_f(T x, int iterations = 50) {
  // 运用费马小定理形成一个概率算法，如果x是素数，那么对于任意的1<=a<x，a^(x-1)
  // ≡ 1 (mod x) 如果x是合数，那么对于大多数的a，a^(x-1) ≡ 1 (mod x)不成立
  // 值得注意的是，这个算法是概率算法，不是绝对的，确实存在一些合数，能够通过这个检验
  // 但是这些合数是非常少的，遇到这些数的概率小于你的电脑被宇宙射线搞坏的概率
  // 所以这个算法是非常有效的
  if (x < 2) return false;
  while (iterations--) {
    T a = rand() * rand() % (x - 1) + 1;
    if (expmod(a, x - 1, x) != 1) return false;
  }
  return true;
}

bool is_prime_[100000 + 1];
template <typename T>
std::vector<T> get_primes() {
  // 埃氏筛，一种比较简单的筛法，时间复杂度为O(nloglogn)
  std::vector<T> primes;
  is_prime_[0] = is_prime_[1] = false;
  std::fill(is_prime_ + 2, is_prime_ + 100000 + 1, true);
  for (size_t i = 2; i <= 100000; ++i) {
    if (is_prime_[i]) {
      primes.push_back(i);
      if ((long long)i * i <= 100000)
        for (size_t j = i * i; j <= 100000; j += i) is_prime_[j] = false;
    }
  }
  return primes;
}

int main() {
  srand(time(nullptr));
  int n;
  cin >> n;

  int sum = 0;

  for (int i = 1; i <= n; ++i) sum += (is_prime(i) ? i : 0);
  // for (int i = 1; i <= n; ++i) sum += (is_prime_f(i) ? i : 0);
  // for (int i : get_primes<int>()) {
  //   if (i > n) break;
  //   sum += i;
  // }

  cout << "The sum of primes:  " << sum << endl;

  return 0;
}
