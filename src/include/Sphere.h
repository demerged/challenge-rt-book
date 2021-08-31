#pragma once
#include "rt.h"
#include "Material.h"
#include "Matrix.h"
#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"

struct Sphere : public Shape{
    tuple origin;
    float radius;
    Sphere();
    bool operator==(const Sphere  &s) const;
    std::vector<Intersection> local_intersect(Ray r) override;
    tuple local_normal_at(const tuple& local_point) override;
    ~Sphere();
};

Sphere glass_sphere();
