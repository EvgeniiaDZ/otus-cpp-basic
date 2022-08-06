#include "std.hpp"
#include <math.h>

Std::Std() : _std(0) {}

void Std::update(double next) {
    _val.push_back(next);
    long double sum = 0;
    for (int value : _val) {
        sum += pow((value - mean()), 2);
    }
    _std = sqrt(sum / _val.size());
}

double Std::eval() const {
    return _std;
}

const char* Std::name() const {
    return "std";		
}

double Std::mean() {
    long double sum = 0;
    for (int value: _val) {
        sum += value ;
    }
    return (_val.size() == 0) ? (0) : (sum / _val.size());
}
