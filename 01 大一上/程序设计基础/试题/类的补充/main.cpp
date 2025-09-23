#include <iostream>

#include "data.h"

int main() {
  double d[] = {1, 2, 3, 4, 5};
  Data data1(d, 5);
  data1.add(6);
  std::cout << "Mean: " << data1.mean() << std::endl;
  std::cout << "Standard deviation: " << data1.std() << std::endl;

  Data data2;
  data2.add(1);
  data2.add(2);
  data2.add(3);
  std::cout << "Mean: " << data2.mean() << std::endl;
  std::cout << "Standard deviation: " << data2.std() << std::endl;
  return 0;
}