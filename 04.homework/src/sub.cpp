#include "sub.hpp"

Sub::Sub(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("-", lhs, rhs)
    , repr_("-") {}


Sub::~Sub() {}


std::string Sub::repr() const { return repr_; }