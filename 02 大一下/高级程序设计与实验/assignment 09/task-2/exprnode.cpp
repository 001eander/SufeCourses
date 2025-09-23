#include "exprnode.h"

bool ExprNode::operator==(const ExprNode& oth) const {
  if (type != oth.type) return false;
  if (type == NodeType::NUM) return value == oth.value;
  if (value != oth.value) return false;
  if (type == NodeType::ADD || type == NodeType::MUL)
    return (*left == *oth.left && *right == *oth.right) ||
           (*left == *oth.right && *right == *oth.left);
  return *left == *oth.left && *right == *oth.right;
}

std::string to_str(const ExprNode& expr, NodeType p_type) {
  if (p_type == NodeType::NUM)
    throw std::runtime_error("Invalid expression type");

  if (expr.type == NodeType::NUM) return integerToString(expr.value);

  auto l_str = to_str(*expr.left, expr.type);
  auto r_str = to_str(*expr.right, expr.type);

  int priority[]{0, 1, 1, 2, 2, 3, 4};

  auto expr_p = priority[static_cast<int>(expr.type)];
  auto p_p = priority[static_cast<int>(p_type)];

  if (expr_p < p_p) return '(' + l_str + char(expr.value) + r_str + ')';
  return l_str + char(expr.value) + r_str;
}

std::string ExprNode::to_string() const {
  //   if (type == NodeType::NUM) return integerToString(value);
  //   auto left_str = left->to_string();
  //   auto right_str = right->to_string();
  //   return '(' + left_str + char(value) + right_str + ')';
  auto l_str = to_str(*left, type);
  auto r_str = to_str(*right, type);
  return l_str + char(value) + r_str;
}

Vector<Vector<int64_t>> gen_perm(const Vector<int64_t>& nums) {
  Vector<Vector<int64_t>> result;
  if (nums.isEmpty()) {
    result.add({});
    return result;
  }
  for (int i = 0; i < nums.size(); ++i) {
    auto sub = nums;
    sub.remove(i);
    auto sub_perms = gen_perm(sub);
    for (const auto& perm : sub_perms) {
      Vector<int64_t> new_perm = {nums[i]};
      new_perm += perm;
      result += new_perm;
    }
  }
  return result;
}

void gen_expr_helper(const Vector<int64_t>& nums, Vector<ExprNode>& results) {
  if (nums.size() == 1) {
    results += ExprNode(nums[0], NodeType::NUM);
    return;
  }

  for (size_t i = 1; i < nums.size(); ++i) {
    auto left_exprs = gen_expr(nums.subList(0, i));
    auto right_exprs = gen_expr(nums.subList(i, nums.size() - i));

    for (const auto& left : left_exprs)
      for (const auto& right : right_exprs)
        for (size_t j = 1; j < 7; ++j)
          results += ExprNode(" +-*/^%"[j], static_cast<NodeType>(j),
                              new ExprNode(left), new ExprNode(right));
  }
}

Vector<ExprNode> gen_expr(const Vector<int64_t>& nums) {
  auto perms = gen_perm(nums);
  Vector<ExprNode> results{};
  for (const auto& perm : perms) {
    Vector<ExprNode> exprs{};
    gen_expr_helper(perm, exprs);
    results += exprs;
  }
  return results;
}

int64_t fpow(int64_t base, int64_t exp) {
  if (exp == 0) return 1;
  if (exp == 1) return base;
  if (exp % 2 == 0) {
    auto half = pow(base, exp / 2);
    return half * half;
  }
  return base * pow(base, exp - 1);
}

bool can_eval(const ExprNode& expr) {
  if (expr.type == NodeType::NUM) return true;
  if (!(can_eval(*expr.left) && can_eval(*expr.right))) return false;
  auto l = eval(*expr.left), r = eval(*expr.right);
  if (expr.type == NodeType::DIV) {
    if (r == 0) return false;
  } else if (expr.type == NodeType::POW) {
    if (l == 0 && r == 0) return false;
    if (r < 0) return false;
  } else if (expr.type == NodeType::MOD) {
    if (l < 0) return false;
    if (r <= 0) return false;
  }
  return true;
}

int64_t eval(const ExprNode& expr) {
  if (!can_eval(expr)) throw std::runtime_error("Invalid expression");
  if (expr.type == NodeType::NUM) return expr.value;
  auto l = eval(*expr.left), r = eval(*expr.right);
  if (expr.type == NodeType::ADD) return l + r;
  if (expr.type == NodeType::SUB) return l - r;
  if (expr.type == NodeType::MUL) return l * r;
  if (expr.type == NodeType::DIV) return l / r;
  if (expr.type == NodeType::POW) return fpow(l, r);
  if (expr.type == NodeType::MOD) return l % r;
  throw std::runtime_error("Invalid expression type");
  return 0;
}

Vector<std::string> gen_expr_str(const Vector<int64_t>& nums, int64_t target) {
  auto exprs = gen_expr(nums);
  Vector<ExprNode> res_exprs{};
  for (const auto& expr : exprs) {
    if (!can_eval(expr)) continue;
    if (eval(expr) == target) {
      bool dul = false;
      for (const auto& e : res_exprs) {
        if (e == expr) {
          dul = true;
          break;
        }
      }
      if (!dul) res_exprs += expr;
    }
  }

  Vector<std::string> dul_res{};
  for (const auto& expr : res_exprs) dul_res += expr.to_string();
  dul_res.sort();

  Vector<std::string> res{};
  for (size_t i = 0; i < dul_res.size(); ++i)
    if (i == 0 || dul_res[i] != dul_res[i - 1]) res += dul_res[i];
  return res;
}
