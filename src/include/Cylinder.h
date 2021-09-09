#pragma once
#include "Shape.h"

struct Cylinder : public Shape {
    Cylinder();
    Cylinder(float min, float max, bool close);
    float minimum, maximum;
    bool closed;
    std::vector<Intersection> local_intersect(Ray r) override;
    tuple local_normal_at(const tuple& local_point) override;
    bool check_cap(Ray r, float t);
    void intersect_caps(Ray r, std::vector<Intersection>& xs);
};