#include <algorithm>
#include <iostream>
using namespace std;

int kthLargest(int arr[], int n, int k) {  // 最简单的方法，直接排序
  sort(arr, arr + n, [](int a, int b) {
    return a > b;
  });  // 利用匿名函数控制降序排序，这是最直接也最直观的方法
  return arr[k - 1];
}

int main() {
  int arr[] = {5, 10, 15, 20, 25};
  int n = sizeof(arr) / sizeof(arr[0]);

  int k = 2;

  int kth = kthLargest(arr, n, k);
  cout << "The " << k << "th largest element is " << kth << endl;

  return 0;
}
