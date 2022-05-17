#pragma once

#include <string>

#include "astnode.hpp"

class Sub : public ASTNode {
    public:
        Sub(ASTNode * lhs, ASTNode * rhs) 
            : ASTNode("-", lhs, rhs)
            , repr_("-") {}

        Sub(const Sub &other) = delete;

        Sub &operator=(const Sub &other) = delete;

        ~Sub() {}

        std::string repr() const { return repr_; }
    private:
        std::string repr_;
};