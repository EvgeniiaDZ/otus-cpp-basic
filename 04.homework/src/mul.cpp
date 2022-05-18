#include "mul.hpp"

Mul::Mul(ASTNode *lhs, ASTNode *rhs) 
    : ASTNode("*", lhs, rhs)
    , repr_("*") {}


Mul::~Mul() {}


std::string Mul::repr() const { return repr_; }