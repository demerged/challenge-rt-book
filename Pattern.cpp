#include "Pattern.h"

Pattern::Pattern() : transform(Matrix::get_identity()), inversed_transform(Matrix::get_identity()){}

void Pattern::set_transform(const Matrix& m){
    transform = m;
    inversed_transform = inverse(transform);
}

Color pattern_at_shape(Pattern* p, Shape* shape, tuple world_point){
    tuple object_point = shape->inversed_transform * world_point;
    tuple pattern_point = p->inversed_transform * object_point;

    return p->pattern_at(pattern_point);
}

TestPattern::TestPattern(){
        a = Color(1, 1, 1);
        b = Color(0, 0, 0);
}
TestPattern::TestPattern(Color a_, Color b_) {
    a = a_;
    b = b_;
}
Color TestPattern::pattern_at(tuple p){
    return Color(p.x, p.y, p.z);
}

