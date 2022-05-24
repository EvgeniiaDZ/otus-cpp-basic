#include "max.hpp"
#include <limits>

Max::Max() 
: _max {std::numeric_limits<double>::min()} {

}

void Max::update(double next) {
    if (next > _max) {
        _max = next;
    }
}

double Max::eval() const {
    return _max;
}

const char* Max::name() const {
    return "max";
} 
#include <limits>