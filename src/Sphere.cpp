#include "Sphere.h"

Sphere::Sphere(){
    origin = point(0, 0, 0);
    radius = 1.0f;
};
Sphere::~Sphere(){}

bool Sphere::operator==(const Sphere  &s) const{
    return origin == s.origin && cmp_f(radius, s.radius);
}

std::vector<Intersection> Sphere::local_intersect(Ray r){
    tuple sphere_to_ray = r.origin - point(0, 0, 0);
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
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

tuple Sphere::local_normal_at(const tuple& local_point) {
    return local_point - point(0, 0, 0);
}

Sphere glass_sphere(){
    Sphere sp = Sphere();
    sp.material.transparency = 1.0;
    sp.material.refractive_index = 1.5;
    return sp;
}