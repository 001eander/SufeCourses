/*
 * File: main.cpp
 * --------------
 * @author: oleander
 *
 * task 2: infix2postfix
 */

// TODO 支持负数

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <map>
#include <vector>

#include "console.h"
#include "simpio.h"
#include "stack.h"
#include "strlib.h"

typedef std::vector<std::string> Expression;

auto is_num = [](std::string str) { return stringIsReal(str); };
auto is_op = [](std::string ch) { return stringContains("+-*/^", ch); };

Expression split(const std::string& str) {
  Expression tokens;

  auto prev = str.begin();
  auto it = str.begin();

  auto is_op_bracket = [](char ch) { return stringContains("+-*/^()", ch); };

  while (it != str.end()) {
    if (is_op_bracket(*it)) {
      if (prev != it) tokens.push_back(std::string(prev, it));

      tokens.push_back(std::string(1, *it));
      prev = it + 1;
    }
    ++it;
  }

  if (prev != it) tokens.push_back(std::string(prev, it));

  return tokens;
}

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
  if (expr.empty()) {
    os << "[]";
    return os;
  }
  os << "[ ";
  for (const auto& ch : expr) {
    os << ch << " ";
  }
  os << "]";
  return os;
}

Expression convert(const Expression& infix) {
  const auto priority = std::map<std::string, int>{
      {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};
  auto cmp = [&priority](std::string a, std::string b) {
    return priority.at(a) < priority.at(b);
  };

  auto is_left = [](std::string ch) { return ch == "("; };
  auto is_right = [](std::string ch) { return ch == ")"; };

  auto stk_op = Stack<std::string>();
  auto stk_tmp = Stack<std::string>();

  for (const auto& ch : infix) {
    if (is_num(ch)) {
      stk_tmp.push(ch);
      continue;
    }

    if (is_op(ch)) {
      if (stk_op.isEmpty()) {
        stk_op.push(ch);
        continue;
      }

      while (!stk_op.isEmpty() && is_op(stk_op.peek()) &&
             !cmp(stk_op.peek(), ch)) {
        stk_tmp.push(stk_op.pop());
      }

      stk_op.push(ch);
      continue;
    }

    if (is_left(ch)) {
      stk_op.push(ch);
      continue;
    }

    if (is_right(ch)) {
      while (!stk_op.isEmpty() && !is_left(stk_op.peek()))
        stk_tmp.push(stk_op.pop());

      if (stk_op.isEmpty()) {
        std::cerr << "Error: unmatched right parenthesis" << std::endl;
        return Expression();
      }

      stk_op.pop();
      continue;
    }
  }

  while (!stk_op.isEmpty()) {
    if (is_left(stk_op.peek())) {
      std::cerr << "Error: unmatched left parenthesis" << std::endl;
      return Expression();
    }
    stk_tmp.push(stk_op.pop());
  }

  auto postfix = Expression();
  while (!stk_tmp.isEmpty()) postfix.push_back(stk_tmp.pop());
  std::reverse(postfix.begin(), postfix.end());
  return postfix;
}

double calc(const Expression& postfix) {
  auto stk = Stack<double>();
  auto num_ = [](std::string str) { return stringToReal(str); };
  auto op_ = [](std::string str) -> std::function<double(double, double)> {
    if (str == "+") {
      return [](double a, double b) { return a + b; };
    } else if (str == "-") {
      return [](double a, double b) { return a - b; };
    } else if (str == "*") {
      return [](double a, double b) { return a * b; };
    } else if (str == "/") {
      return [](double a, double b) { return a / b; };
    } else if (str == "^") {
      return [](double a, double b) { return std::pow(a, b); };
    }
    std::cerr << "Error: invalid operator" << std::endl;
    return [](double, double) { return 0; };
  };

  for (auto ch : postfix) {
    if (is_num(ch)) {
      stk.push(num_(ch));
      continue;
    }

    if (is_op(ch)) {
      if (stk.size() < 2) {
        std::cerr << "Error: invalid postfix expression" << std::endl;
        return 0;
      }

      auto b = stk.pop();
      auto a = stk.pop();
      stk.push(op_(ch)(a, b));
      continue;
    }
  }

  return stk.pop();
}

int main() {
  auto input = getLine("Enter an infix expression: ");
  // auto input = "1.0+((2.2+3)*4^2)-5.96";

  auto infix = split(input);
  std::cout << "Infix:   " << infix << std::endl;

  auto postfix = convert(infix);

  std::cout << "Postfix: " << postfix << std::endl;

  auto result = calc(postfix);
  std::cout << "Result:  " << result << std::endl;

  return EXIT_SUCCESS;
}
