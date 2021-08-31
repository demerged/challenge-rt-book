#pragma once
#include <algorithm>
#include "rt.h"
#include "Ray.h"
#include "Sphere.h"

struct Computation{
    float t;
    Shape* s;
    tuple p;
    tuple eyev;
    tuple normalv;
    tuple over_point;
    tuple under_point;
    tuple reflectv;
    bool inside;
    float n1, n2;
    Computation();
};

Computation prepare_computations(const Intersection& i, Ray& r, const std::vector<Intersection>& xs = {});