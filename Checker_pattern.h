#pragma once
#include "Pattern.h"

struct Checker_pattern : public Pattern {
    Checker_pattern(Color a_, Color b_);

    Color pattern_at(tuple point) override;
};