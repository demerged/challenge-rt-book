#pragma once
#include <cmath>
#include "rt.h"
#include "Matrix.h"
#include "Shape.h"

struct Pattern {
    Pattern();
    Color a;
    Color b;
    Matrix transform;
    Matrix inversed_transform;

    void set_transform(const Matrix& m);
    virtual Color pattern_at(tuple pattern_point) = 0;
};


struct TestPattern : public Pattern {
    TestPattern();
    TestPattern(Color a_, Color b_);
    Color pattern_at(tuple p);
};

Color pattern_at_shape(Pattern* p, Shape* shape, tuple world_point);
