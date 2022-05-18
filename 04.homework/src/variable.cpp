#include "variable.hpp"

Variable::Variable(std::string name)
    : ASTNode(name)
    , name_(name) {}


Variable::~Variable() {}


std::string Variable::name() const { return name_; }