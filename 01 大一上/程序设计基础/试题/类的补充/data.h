#ifndef DATA_H
#define DATA_H

class Data {
 public:
  Data();
  Data(double d[], int n);
  ~Data();
  void add(double x);
  double mean();
  double std();

 private:
  double* data;
  int n;
};

#endif  // DATA_H