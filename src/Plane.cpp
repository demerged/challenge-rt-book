#include "Plane.h"

Plane::~Plane(){}

std::vector<Intersection> Plane::local_intersect(Ray r) {
    if (std::fabs(r.direction.y) < EPSILON) return {};
    float t = -r.origin.y / r.direction.y;
    return {Intersection(t, this)};
}

tuple Plane::local_normal_at(const tuple& local_point) {
    return vector(0, 1, 0);
}