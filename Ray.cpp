#pragma once
#include "matrix.h"
#include <algorithm>
#include "Material.h"

struct Ray{
    tuple origin;
    tuple direction;
    Ray(const tuple &o, const tuple &d): origin(o), direction(d) {};

    tuple position(float t){
        return origin + direction * t;
    }
    Ray transform(Matrix m);
};

Ray Ray::transform(Matrix m) {
    Ray result(m * origin, m * direction);
    return result;
}

tuple reflect(tuple &in, tuple &normal) {
    return in - normal * 2 * dot(in, normal);
}


