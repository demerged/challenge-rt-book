#pragma once
#include "Pattern.h"
#include <stdlib.h>
#include <time.h>

struct Experimental_pattern : public Pattern {
    Experimental_pattern(Color a_, Color b_);

    Color pattern_at(tuple point) override;
};
