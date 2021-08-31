#pragma once
#include "Shape.h"
#include <cmath>

struct tpair;
struct Cube : Shape{
    std::vector<Intersection> local_intersect(Ray r) override;
    tuple local_normal_at(const tuple& local_point) override;
};

tpair check_axis(float origin, float direction);
