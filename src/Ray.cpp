#include "Ray.h"

Ray::Ray(const tuple &o, const tuple &d): origin(o), direction(d) {};

tuple Ray::position(float t){
    return origin + direction * t;
}

Ray Ray::transform(Matrix& m) {
    Ray result(m * origin, m * direction);
    return result;
}

tuple reflect(tuple &in, tuple &normal) {
    return in - normal * 2 * dot(in, normal);
}


