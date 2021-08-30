#pragma once
#include <vector>
#include "Matrix.h"
#include "Material.h"
#include "Intersection.h"
#include "Ray.h"

struct Shape {
    Shape();
    Matrix transform;
    Material material;
    Matrix inversed_transform;
    void set_transform(const Matrix& m);
    std::vector<Intersection> intersect(Ray r);
    tuple normal_at(const tuple& world_point);
    virtual std::vector<Intersection> local_intersect(Ray r) = 0;
    virtual tuple local_normal_at(const tuple& local_point) = 0;
    virtual ~Shape() = default;
};

struct TestShape : public Shape {
    TestShape();
    std::vector<Intersection> local_intersect(Ray r) override;
    tuple local_normal_at(const tuple& local_point) override;
    Ray saved_ray;
};
