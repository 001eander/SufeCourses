#include "console.h"
#include <fstream>
#include <iostream>

using namespace std;

class Cake {
public:
  virtual double cakeprice() const = 0; // 纯虚函数
  Cake(double d, double p) {            // 构造函数
    density = d;
    unit_price = p;
  };
  double get_unitPrice() const { // 成员函数，返回单价：元/克
    return unit_price;
  };
  double get_density() const { // 成员函数，返回密度：克/立方厘米
    return density;
  };

private:
  double density;    // 蛋糕的密度：克/立方厘米
  double unit_price; // 单价：元/克
};

class CubiodCake : public Cake {
private:
  double length;
  double width;
  double height;

public:
  CubiodCake(double l, double w, double h, double d, double p)
      : Cake(d, p), length(l), width(w), height(h) {}
  double cakeprice() const;
};

class CylinderCake : public Cake {
private:
  double radius;
  double height;

public:
  CylinderCake(double r, double h, double d, double p)
      : Cake(d, p), radius(r), height(h) {}
  double cakeprice() const;
};

/* (1)请在此处实现 CubiodCake 的成员函数 cakeprice()，返回特定的某个长方体
形状蛋糕的价格，计算公式：蛋糕价格=体积*密度*单价。*/

double CubiodCake::cakeprice() const {
  auto volume = length * width * height;
  return volume * get_density() * get_unitPrice();
}

/* (2)请在此处实现 CylinderCake 的成员函数 cakeprice()，返回特定的某个圆柱体
形状蛋糕的价格，计算公式：蛋糕价格=体积*密度*单价。*/

double CylinderCake::cakeprice() const {
  auto volume = 3.14159 * radius * radius * height;
  return volume * get_density() * get_unitPrice();
}

int main() {
  ifstream inputFile("cakes.txt");
  // (3) 请在此处建立 ofstream 类对象 outputFile，并同时打开磁盘文件
  // totalcost.txt

  ofstream outputFile("totalcost.txt");

  // (4) 请修改下面 if 语句的条件，判断是否成功打开了文件
  if (!outputFile.is_open()) {
    cerr << "Error opening files!" << endl;
    return 1;
  }
  double totalCost = 0;
  char type;
  // 以下用 inputFile 对象依次读取 cakes.txt
  // 中的每一行数据，并根据每一行的类型进行计算。
  /* (5) 请修改下面 while 语句中的 true 条件部分，读取 cakes.txt
中每一行数据的蛋糕类型 type， 提示：请用操作符>>读取，该操作若读取成功返回
ture,若遇文件结束则返回 false。*/
  while (inputFile >> type) {
    if (type == 'U') {
      double length = 0, width = 0, height = 0, density = 0, price = 0;
      // (6) 请从磁盘文件依次读入 length，width，height，price
      inputFile >> length >> width >> height >> price;
      CubiodCake cubiodCake(length, width, height, density, price);
      totalCost += cubiodCake.cakeprice();
    } else if (type == 'Y') {
      double radius = 0, height = 0, density = 0, price = 0;
      //(7) 请从磁盘文件依次读入 height，radius，price
      inputFile >> height >> radius >> price;
      CylinderCake cylinderCake(radius, height, density, price);
      totalCost += cylinderCake.cakeprice();
    }
  }
  cout << totalCost;
  // (8) 请在此处将计算得到的 totalCost 的值写入磁盘文件 totalcost.txt
  outputFile << totalCost;
  // (9) 请在此处关闭打开的所有文件
  inputFile.close();
  outputFile.close();
  return 0;
}
