#include "Checker_pattern.h"

Checker_pattern::Checker_pattern(Color a_, Color b_) {
    a = a_;
    b = b_;
}

Color Checker_pattern::pattern_at(tuple point){
    int point_sum = std::floor(point.x) + std::floor(point.y) + std::floor(point.z);
    if (point_sum % 2 == 0){
        return a;
    }
    return b;
}
