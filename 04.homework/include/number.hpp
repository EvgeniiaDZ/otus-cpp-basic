#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode {
  public:
    explicit Number(int val);
    Number(const Number &other) = delete;
    Number &operator=(const Number &other) = delete;
    ~Number();

    int value() const;

  private:
    int val_;
};
