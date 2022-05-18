#pragma once

#include <string>

#include "astnode.hpp"

class Variable : public ASTNode {
    public:
        explicit Variable(std::string name);
        Variable(const Variable &other) = delete;
        Variable &operator=(const Variable &other) = delete;
        ~Variable();

        std::string name() const;

    private:
        std::string name_;

};