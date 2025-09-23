#include <iostream>

using namespace std;

int *remove_repeat(int a[], int n, int &m, int *minr, int *maxr) {
  int *b = new int[n];

  m = 0;
  *maxr = 0;
  *minr = 0x7fffffff;

  int r = 1;
  b[m++] = a[0];

  for (int i = 1; i < n; i++) {
    if (b[m - 1] != a[i]) {
      b[m++] = a[i];
      *minr = min(*minr, (r == 1 ? *minr : r));  // 修正minr
      *maxr = max(*maxr, r);
      r = 1;
    } else {
      r++;
    }
  }

  int *tmp = b;
  b = new int[m];
  for (int i = 0; i < m; i++) b[i] = tmp[i];
  delete[] tmp;
  return b;
}

int main() {
  int a[] = {1, 2, 2, 2, 2, 3, 3, 3, 4, 5};
  int n = sizeof(a) / sizeof(int);

  int m, minr, maxr;
  int *p = remove_repeat(a, n, m, &minr, &maxr);

  cout << m << endl;  // should output: 5
  for (int i = 0; i < m; i++) {
    cout << p[i] << ' ';  // should output: 1 2 3 4 5
  }
  cout << endl;
  cout << minr << ' ' << maxr << endl;  // should output: 3 4

  delete p;
  return 0;
}
