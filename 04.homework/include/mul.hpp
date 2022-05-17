#pragma once 

#include <string>

#include "astnode.hpp"

class Mul : public ASTNode {
    public:
        Mul(ASTNode * lhs, ASTNode * rhs)
            : ASTNode("*", lhs, rhs)
            , repr_("*") {}

        Mul(const Mul &other) = delete;

        Mul &operator=(const Mul &other) = delete;

        ~Mul() {}

        std::string repr() const { return repr_; }

    private:
  
        std::string repr_;
};