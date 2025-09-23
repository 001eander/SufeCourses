/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cassert>
#include <cstdlib>

#include "console.h"
#include "simpio.h"

#include "data.h"

int main()
{
    Vector<double> data = {1, 2, 3, 4, 4, 4};
    Data data1 = data;

    std::cout << "mean: 3, std: 1.333" << std::endl;

    std::cout << data1.mean() << " " << data1.std() << std::endl;

    Data data2;

    data2.add(1);
    data2.add(2);
    data2.add(3);
    data2.add(4);
    data2.add(4);
    data2.add(4);

    std::cout << data2.mean() << " " << data2.std() << std::endl;

    return EXIT_SUCCESS;
}
