#include <format>
#include <iostream>

using namespace std;

void solve(double** A, double* b, const int n, double** L, double** U,
           double* y, double* x) {
  double** tmp = new double*[n + 1];
  for (int i = 0; i <= n; i++) tmp[i] = new double[n + 1];
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++) tmp[i][j] = A[i][j];

  for (size_t k = 1; k <= n - 1; ++k) {
    size_t p = k;
    for (size_t i = k; i <= n; ++i)
      if (A[i][k] > A[p][k]) p = i;
    for (size_t j = 1; j <= n; ++j) swap(A[k][j], A[p][j]);
    if (A[k][k]) {
      for (size_t i = k + 1; i <= n; ++i) {
        A[i][k] /= A[k][k];
        for (size_t j = k + 1; j <= n; ++j) A[i][j] -= A[i][k] * A[k][j];
      }
    } else {
      break;
    }
  }

  for (size_t i = 1; i <= n; ++i) {
    for (size_t j = 1; j <= n; ++j) {
      L[i][j] = ((i == j) ? 1 : ((i > j) ? A[i][j] : 0));
      U[i][j] = ((i <= j) ? A[i][j] : 0);
      A[i][j] = tmp[i][j];
    }
    delete[] tmp[i];
  }
  delete[] tmp;

  for (size_t i = 1; i <= n; ++i) {
    y[i] = b[i];
    for (size_t j = 1; j <= i - 1; ++j) y[i] -= L[i][j] * y[j];
  }

  for (size_t i = n; i >= 1; --i) {
    x[i] = y[i];
    for (size_t j = i + 1; j <= n; ++j) x[i] -= U[i][j] * x[j];
    x[i] /= U[i][i];
  }
}

int main() {
  // const int n = 84;
  const int n = 4;

  double** A = new double*[n + 1];
  double* b = new double[n + 1];
  double** L = new double*[n + 1];
  double** U = new double*[n + 1];
  double* y = new double[n + 1];
  double* x = new double[n + 1];

  for (int i = 1; i <= n; i++) {
    A[i] = new double[n + 1];
    L[i] = new double[n + 1];
    U[i] = new double[n + 1];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) A[i][j] = 0;
    A[i][i] = 6;
    A[i][i - 1] = 8;
    A[i - 1][i] = 1;
    b[i] = 15;
  }
  b[1] = 7;
  b[n] = 14;

  solve(A, b, n, L, U, y, x);

  constexpr auto fmt_str = "{:10.5f}";

  cout << "A" << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cout << format(fmt_str, A[i][j]);
    cout << endl;
  }

  cout << "b" << endl;
  for (int i = 1; i <= n; i++) cout << format(fmt_str, b[i]);

  cout << endl << "L" << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cout << format(fmt_str, L[i][j]);
    cout << endl;
  }
  cout << "U" << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) cout << format(fmt_str, U[i][j]);
    cout << endl;
  }

  cout << "y" << endl;
  for (int i = 1; i <= n; i++) cout << format(fmt_str, y[i]);

  cout << endl << "x" << endl;
  for (int i = 1; i <= n; i++) cout << format(fmt_str, x[i]);
  cout << endl;

  for (int i = 0; i < n; i++) {
    delete[] A[i];
    delete[] L[i];
    delete[] U[i];
  }
  delete[] A;
  delete[] b;
  delete[] L;
  delete[] U;
  delete[] y;
  delete[] x;

  return 0;
}