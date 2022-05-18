#include "number.hpp"

Number::Number(int val) 
    : ASTNode(std::to_string(val))
    , val_(val) {}


Number::~Number() {}


int Number::value() const { return val_; }