#include "Pattern.cpp"

struct Gradient_pattern : public Pattern {
    Gradient_pattern(Color a_, Color b_) {
        a = a_;
        b = b_;
    }
    Color pattern_at(tuple pattern_point) override;
};

Color Gradient_pattern::pattern_at(tuple pattern_point) {
    Color distance = b - a;
    float fraction = pattern_point.x - std::floor(pattern_point.x);

    return a + distance * fraction;
}