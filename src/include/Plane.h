#pragma once
#include "Shape.h"

struct Plane : public Shape {
    std::vector<Intersection> local_intersect(Ray r) override;
    tuple local_normal_at(const tuple& local_point) override;
    ~Plane();
};
