#include "Pattern.cpp"
#include <stdlib.h>
#include <time.h> 


struct Experimental_pattern : public Pattern {
    Experimental_pattern(Color a_, Color b_) {
        a = a_;
        b = b_;
        srand (time(NULL));
    }

    Color pattern_at(tuple point) override;
};

Color Experimental_pattern::pattern_at(tuple point){
    float r,g,b;
    r = (rand() % 255 + 1) / 255.f;
    g = (rand() % 255 + 1) / 255.f;
    b = (rand() % 255 + 1) / 255.f;
    return Color(r, g, b);
}
