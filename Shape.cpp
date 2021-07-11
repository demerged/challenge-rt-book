#pragma once
#include <vector>
#include "matrix.h"
#include "Material.h"
#include "Intersection.cpp"
#include "Ray.cpp"

struct Shape {
    Matrix transform = Matrix::get_identity();
    Material material;
    void set_transform(const Matrix& m);
    std::vector<Intersection> intersect(Ray r);
    tuple normal_at(const tuple &world_point);
    virtual std::vector<Intersection> local_intersect(Ray r) = 0;
};

void Shape::set_transform(const Matrix& m) {
    transform = m;
}

std::vector<Intersection> Shape::intersect(Ray r) {
    Matrix t = inverse(transform);
    Ray local_ray = r.transform(t);
    return local_intersect(local_ray);
}

tuple Shape::normal_at(const tuple &world_point) {
    tuple object_point = inverse(transform) * world_point;
    tuple object_normal = object_point - point(0, 0, 0);
    tuple world_normal = transpose(inverse(transform)) * object_normal;
    world_normal.w = 0;
    return normalize(world_normal);
}



struct TestShape : public Shape {
    std::vector<Intersection> local_intersect(Ray r) override;
};

std::vector<Intersection> TestShape::local_intersect(Ray r) {
    return {};
}
