#include "mean.hpp"
#include "mean.hpp"

Mean::Mean() 
    : _mean(0)
    , _sum(0)
    , _count(0) {}

void Mean::update(double next) {
    _sum += next;
    ++_count;
    _mean = _sum / _count;
}

double Mean::eval() {
    return _mean;
}

const char* Mean::name() const {
    return "mean";
}
