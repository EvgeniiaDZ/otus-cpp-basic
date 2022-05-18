#include "add.hpp"

Add::Add(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("+", lhs, rhs)
    , repr_("+") {}


Add::~Add() {}


std::string Add::repr() const { return repr_; }