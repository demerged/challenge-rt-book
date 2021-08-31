#include "Experimental_pattern.h"

Experimental_pattern::Experimental_pattern(Color a_, Color b_) {
    a = a_;
    b = b_;
    srand (time(NULL));
}

Color Experimental_pattern::pattern_at(tuple point){
    // float r,g,b;
    // r = (rand() % 255 + 1) / 255.f;
    // g = (rand() % 255 + 1) / 255.f;
    // b = (rand() % 255 + 1) / 255.f;
    // return Color(r, g, b);

    if ((rand() % 2)-1)
        return Color(1, 1, 1);
    return Color(0, 0, 0);
}
