#ifndef EXPRNODE_H
#define EXPRNODE_H

#include <algorithm>
#include <cstdint>
#include <string>

#include "strlib.h"
#include "vector.h"

enum class NodeType { NUM, ADD, SUB, MUL, DIV, POW, MOD };

class ExprNode {
 public:
  NodeType type;
  int64_t value;
  ExprNode *left, *right;
  ExprNode(int64_t value, NodeType type)
      : type(type), value(value), left(nullptr), right(nullptr) {}
  ExprNode(int64_t value, NodeType type, ExprNode* left, ExprNode* right)
      : type(type), value(value), left(left), right(right) {}

  ExprNode(const ExprNode& other)
      : type(other.type),
        value(other.value),
        left(other.left ? new ExprNode(*other.left) : nullptr),
        right(other.right ? new ExprNode(*other.right) : nullptr) {}

  ExprNode& operator=(const ExprNode& other) {
    if (this != &other) {
      if (left) delete left;
      if (right) delete right;

      type = other.type;
      value = other.value;
      left = other.left ? new ExprNode(*other.left) : nullptr;
      right = other.right ? new ExprNode(*other.right) : nullptr;
    }
    return *this;
  }

  ~ExprNode() {
    if (left) delete left;
    if (right) delete right;
  }

  bool operator==(const ExprNode&) const;
  std::string to_string() const;
  std::ostream& operator<<(std::ostream& os) const { return os << to_string(); }
};

Vector<Vector<int64_t>> gen_perm(const Vector<int64_t>& nums);
void gen_expr_helper(const Vector<int64_t>& nums, Vector<ExprNode>& results);
Vector<ExprNode> gen_expr(const Vector<int64_t>& nums);
bool can_eval(const ExprNode& expr);
int64_t eval(const ExprNode& expr);

Vector<std::string> gen_expr_str(const Vector<int64_t>& nums, int64_t target);
#endif  // EXPRNODE_H
