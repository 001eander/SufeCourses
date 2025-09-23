#include <iostream>
using namespace std;

struct Point {
  int x, y;
};

int main() {
  int n, m;
  cin >> n >> m;
  Point p;
  cin >> p.x >> p.y;
  // 注意数组下标从零开始
  Point **nxt = new Point *[n + 1];
  nxt[0] = nullptr;
  for (int i = 1; i <= n; i++) {
    nxt[i] = new Point[m + 1];
    for (int j = 1; j <= m; j++) cin >> nxt[i][j].x >> nxt[i][j].y;
  }

  while (p.x != 0 && p.y != 0) {
    cout << p.x << ' ' << p.y << endl;
    p = nxt[p.x][p.y];
  }

  for (int i = 1; i <= n; i++) delete[] nxt[i];
  delete[] nxt;
  return 0;
}
