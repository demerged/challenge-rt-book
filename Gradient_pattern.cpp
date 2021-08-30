#include "Gradient_pattern.h"


Gradient_pattern::Gradient_pattern(Color a_, Color b_) {
    a = a_;
    b = b_;
}

Color Gradient_pattern::pattern_at(tuple pattern_point) {
    Color distance = Gradient_pattern::b - Gradient_pattern::a;
    // function from book:
    float fraction = pattern_point.x - std::floor(pattern_point.x);
    // function that gives correct image:
    // float fraction = (pattern_point.x +1.0) * 0.5;

    return Gradient_pattern::a + distance * fraction ;
}