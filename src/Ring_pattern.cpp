#include "Ring_pattern.h"

Ring_pattern::Ring_pattern(Color a_, Color b_) {
    a = a_;
    b = b_;
}

Color Ring_pattern::pattern_at(tuple p) {
    float const x2 = p.x * p.x;
    float const z2 = p.z * p.z;
    float const magnitude = std::sqrt(x2 + z2);
    bool isEven = (((int)std::floor(magnitude)) % 2) == 0;
    return isEven ? a : b;
}