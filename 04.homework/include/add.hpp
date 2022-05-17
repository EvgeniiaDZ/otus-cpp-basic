#pragma once 

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
    public:
        Add(ASTNode * lhs, ASTNode * rhs)
            : ASTNode( "+", lhs, rhs )
            , repr_("+") {}

        Add(const Add &other) = delete;

        Add &operator=(const Add &other) = delete;

        ~Add() {}

        std::string repr() const { return repr_; }
    private:
        std::string repr_;
};