#pragma once

#include <string>

#include "astnode.hpp"

class Div : public ASTNode {
    public:
        Div(ASTNode *lhs, ASTNode *rhs);        
        Div(const Div &other) = delete;
        Div &operator=(const Div &other) = delete;
        ~Div();

        std::string repr() const;
    
    private:
        std::string repr_;
};