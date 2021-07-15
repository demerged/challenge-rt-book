#pragma once
#include <cmath>
#include "rt.h"
#include "matrix.h"
#include "Shape.cpp"

struct Pattern {
    Color a;
    Color b;
    Matrix transform = Matrix::get_identity();
    Matrix inversed_transform = Matrix::get_identity();
    
    void set_transform(const Matrix& m);
    Color pattern_at_shape(Pattern* p, Shape* shape, tuple world_point);
    virtual Color pattern_at(tuple pattern_point) = 0;
};

void Pattern::set_transform(const Matrix& m){
    transform = m;
    inversed_transform = inverse(transform);
}

Color pattern_at_shape(Pattern* p, Shape* shape, tuple world_point){
    tuple object_point = shape->inversed_transform * world_point;
    tuple pattern_point = p->inversed_transform * object_point;

    return p->pattern_at(pattern_point);
}


struct TestPattern : public Pattern {
    TestPattern(Color a_, Color b_) {
        a = a_;
        b = b_;
    }
    Color pattern_at(tuple p){
        return Color(p.x, p.y, p.z);
    }
};