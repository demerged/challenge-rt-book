#include "Pattern.h"

struct Stripe_pattern : public Pattern {
    Stripe_pattern(Color a_, Color b_);
    Color pattern_at(tuple pattern_point) override;
};
