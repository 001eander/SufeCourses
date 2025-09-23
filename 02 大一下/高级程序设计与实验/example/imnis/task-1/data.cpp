#include "data.h"

Data::Data() {}

Data::Data(Vector<double> d)
    : data(d)
{}

void Data::add(double x)
{
    data += x;
}

double Data::mean()
{
    double sum = 0.0;

    for (auto item : data)
        sum += item;

    return sum / data.size();
}

double Data::std()
{
    double sq_div = 0.0;
    double mean = this->mean();

    for (auto item : data)
        sq_div += (item - mean) * (item - mean);

    return sq_div / data.size();
}
