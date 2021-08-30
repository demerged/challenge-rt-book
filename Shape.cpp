#include "Shape.h"

Shape::Shape() : transform(Matrix::get_identity()), inversed_transform(Matrix::get_identity()){}

void Shape::set_transform(const Matrix& m) {
    transform = m;
    inversed_transform = inverse(transform);
}

std::vector<Intersection> Shape::intersect(Ray r) {
    Matrix t = inversed_transform;
    Ray local_ray = r.transform(t);
    return local_intersect(local_ray);
}

tuple Shape::normal_at(const tuple& world_point) {
    tuple local_point = inversed_transform * world_point;
    tuple local_normal = local_normal_at(local_point);
    tuple world_normal = transpose(inversed_transform) * local_normal;
    world_normal.w = 0;
    return normalize(world_normal);
}

TestShape::TestShape() : saved_ray(Ray(point(0, 0, 0), point(0, 0, 0))){}
std::vector<Intersection> TestShape::local_intersect(Ray r) {
    saved_ray = r;
    return {};
}

tuple TestShape::local_normal_at(const tuple& p) {
    return vector(p.x, p.y, p.z);
}
