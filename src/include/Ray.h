#pragma once
#include "Matrix.h"
#include "Material.h"
#include <algorithm>

struct Ray{
    tuple origin;
    tuple direction;
    Ray(const tuple &o, const tuple &d);

    tuple position(float t);
    Ray transform(Matrix& m);
};

tuple reflect(tuple &in, tuple &normal);
