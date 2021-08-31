#include "Stripe_pattern.h"

Stripe_pattern::Stripe_pattern(Color a_, Color b_) {
    a = a_;
    b = b_;
}

Color Stripe_pattern::pattern_at(tuple pattern_point){
    if (int(floor(pattern_point.x)) % 2 == 0)
        return a;
    return b;
}
