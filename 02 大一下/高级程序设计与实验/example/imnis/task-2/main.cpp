/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "vector.h"

#include <cstdlib>
#include <fstream>
#include <string>

int main()
{
    std::ifstream data("data.txt");
    std::ifstream words("words.txt");

    Vector<std::string> lines;

    std::string str;
    while (std::getline(data, str))
        lines += str;

    Vector<std::string> word_list;
    while (std::getline(words, str))
        word_list += str;

    Vector<std::string> wdata = lines;

    for (size_t i = 0; i != lines[0].size(); ++i) {
        str = "";
        for (size_t j = 0; j != lines.size(); ++j)
            str += lines[j][i];
        wdata += str;
    }

    int cnt = 0;
    for (auto word : wdata) {
        for (auto w : word_list) {
            if (w == word) {
                std::cout << w << std::endl;
                cnt++;
            }
        }
    }
    std::cout << cnt << std::endl;
    return EXIT_SUCCESS;
}
