#include <iostream>
using namespace std;

int value(int num[], int n) {
  if (n == 0) return 0;
  if (n == 1) return num[0];
  return max(num[0] + value(num + 2, n - 2),
             value(num + 1, n - 1));  // 考虑这个鸡窝里要不要拿鸡蛋
}

int main() {
  int n;
  cin >> n;

  int num[1000];
  for (int i = 0; i < n; i++) {
    cin >> num[i];
  }

  cout << value(num, n) << endl;
  return 0;
}
