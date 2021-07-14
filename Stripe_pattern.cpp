#include "Pattern.cpp"

struct Stripe_pattern : public Pattern {
    Stripe_pattern(Color a_, Color b_) {
        a = a_;
        b = b_;
    }

    Color pattern_at(tuple pattern_point) override;
};

Color Stripe_pattern::pattern_at(tuple pattern_point){
    if (int(floor(pattern_point.x)) % 2 == 0)
        return a;
    return b;
}
