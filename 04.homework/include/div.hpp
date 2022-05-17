#pragma once

#include <string>

#include "astnode.hpp"

class Div : public ASTNode {
    public:
        Div(ASTNode * lhs, ASTNode * rhs)
            : ASTNode( "/", lhs, rhs)
            , repr_("/") {}

        Div(const Div &other) = delete;

        Div &operator=(const Div &other) = delete;

        ~Div() {}

        std::string repr() const { return repr_; }
    
    private:
        std::string repr_;
};