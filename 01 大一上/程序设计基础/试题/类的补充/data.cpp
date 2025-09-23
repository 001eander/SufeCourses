#include "data.h"

#include <cmath>

Data::Data() : data(nullptr), n(0) {}

Data::Data(double d[], int n) : data(new double[n]), n(n) {
  for (int i = 0; i < n; ++i) data[i] = d[i];
}

Data::~Data() { delete[] data; }

void Data::add(double x) {
  double* new_data = new double[n + 1];
  for (int i = 0; i < n; ++i) new_data[i] = data[i];
  new_data[n] = x;
  delete[] data;
  data = new_data;
  ++n;
}

double Data::mean() {
  double sum = 0;
  for (int i = 0; i < n; ++i) sum += data[i];
  return sum / n;
}

double Data::std() {
  double m = mean();
  double sum = 0;
  for (int i = 0; i < n; ++i) sum += (data[i] - m) * (data[i] - m);
  return sqrt(sum / n);
}