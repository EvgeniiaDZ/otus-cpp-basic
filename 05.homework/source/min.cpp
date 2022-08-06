#include "min.hpp"
#include <limits>

Min::Min() : m_min{std::numeric_limits<double>::max()} {
}

void Min::update(double next) {
    if (next < m_min) {
        m_min = next;
    }
}

double Min::eval() {
    return m_min;
}

const char* Min::name() const {
    return "min";
}
