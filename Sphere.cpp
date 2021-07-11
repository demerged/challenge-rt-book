#pragma once
#include "rt.h"
#include "Material.h"
#include "matrix.h"
#include "Intersection.cpp"
#include "Ray.cpp"


struct Sphere : public Shape{
    tuple origin;
    float radius;
    Sphere(){
        origin = point(0, 0, 0);
        radius = 1.0f;
    };
    bool operator==(const Sphere  &s) const{
        return origin == s.origin && cmp_f(radius, s.radius);
    }

    std::vector<Intersection> local_intersect(Ray r) override;
};

std::vector<Intersection> Sphere::local_intersect(Ray local_ray){
    tuple sphere_to_ray = local_ray.origin - point(0, 0, 0);
    float a = dot(local_ray.direction, local_ray.direction);
    float b = 2 * dot(local_ray.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;
    float discriminant = b*b - 4 * a * c;

    if (discriminant < 0)
        return {};
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 > t2) std::swap(t1, t2);
    Intersection i1(t1, this);
    Intersection i2(t2, this);
    return intersections(i1, i2);
}