#include "div.hpp"

Div::Div(ASTNode *lhs, ASTNode *rhs)
    : ASTNode( "/", lhs, rhs)
    , repr_("/") {}


Div::~Div() {}

std::string Div::repr() const { return repr_; }