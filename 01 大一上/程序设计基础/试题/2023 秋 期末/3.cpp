#include <iostream>
#include <string>
using namespace std;

bool cmp(char a, char b) {
  if (islower(a) && islower(b)) return a > b;
  if (isupper(a) && isupper(b)) return a < b;
  if (islower(a) && isupper(b)) return false;
  return true;
}

bool isBigger(char s1[], char s2[], int k) {
  for (int i = 0; i < k; i++) {
    if (s1[i] == s2[i]) continue;
    return cmp(s1[i], s2[i]);
  }
  return false;
}

int main() {
  int n, k;
  cin >> n >> k;

  char st[1000][1000];
  for (int i = 0; i < n; i++) {
    cin >> st[i];
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (isBigger(st[i], st[j], k)) {
        swap(st[i], st[j]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << st[i] << endl;
  }

  return 0;
}
