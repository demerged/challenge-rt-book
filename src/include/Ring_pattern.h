#include "Pattern.h"
#include <cmath>

struct Ring_pattern : public Pattern {
    Ring_pattern(Color a_, Color b_);
    Color pattern_at(tuple p) override;
};
