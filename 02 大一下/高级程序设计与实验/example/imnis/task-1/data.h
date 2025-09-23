#ifndef DATA_H
#define DATA_H

#include "vector.h"

class Data
{
private:
    Vector<double> data;

public:
    Data();                 // 默认构造函数，初始化一个空数据列表
    Data(Vector<double> a); // 以 a 中的数据，初始化数据列表

    void add(double x); // 向数据列表里添加元素 x
    double mean();      // 返回当前数据列表中数据的均值
    double std();       // 返回当前数据列表中数据的标准差
};

#endif // DATA_H
