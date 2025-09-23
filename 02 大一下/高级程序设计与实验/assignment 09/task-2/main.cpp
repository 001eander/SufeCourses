/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include <cstdlib>
#include <format>

#include "console.h"
#include "exprnode.h"
#include "simpio.h"

int main() {
  for (const auto& expr : gen_expr_str({1, 2, 3, 4}, 24))
    std::cout << std::format("{:>12} = {}", expr, 24) << std::endl;
  return EXIT_SUCCESS;
}
