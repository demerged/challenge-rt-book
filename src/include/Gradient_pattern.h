#pragma once
#include "Pattern.h"

struct Gradient_pattern : public Pattern {
    Gradient_pattern(Color a_, Color b_);
    Color pattern_at(tuple pattern_point) override;
};
