#pragma once
#include "matrix.h"
#include <algorithm>
#include "Material.h"

struct Ray{
    tuple origin;
    tuple direction;
    Ray(const tuple &o, const tuple &d): origin(o), direction(d) {};

    tuple position(float t){
        return origin + direction * t;
    }
};

struct Sphere{
    tuple origin;
    float radius;
    Material material;
    Matrix transform = Matrix::get_identity();
    Sphere(){
        origin = point(0, 0, 0);
        radius = 1.0f;
        material = Material();
    };
    bool operator==(const Sphere  &s) const{
        return origin == s.origin && cmp_f(radius, s.radius);
    }

    void set_transform(const Matrix& t) {
        transform = t;
    }
};

struct Intersection{
    float t;
    Sphere s;
    bool none;
    Intersection(float t_, Sphere const& s_) : t(t_), s(s_) { none = false; };
    Intersection(bool n) { none = true; }

    bool operator<(const Intersection& i) const {
        return (t < i.t);
    }

    bool operator==(const Intersection& i) const{
        return (cmp_f(t, i.t)) && (s == i.s);
    }
};


std::vector<Intersection> intersections(Intersection i1, Intersection i2){
    std::vector<Intersection> xs;
    xs.push_back(i1);
    xs.push_back(i2);
    return xs;
}

std::vector<Intersection> intersections(Intersection i1, Intersection i2, Intersection i3) {
    std::vector<Intersection> xs;
    xs.push_back(i1);
    xs.push_back(i2);
    xs.push_back(i3);
    return xs;
}


std::vector<Intersection> intersections(Intersection i1, Intersection i2, Intersection i3, Intersection i4) {
    std::vector<Intersection> xs;
    xs.push_back(i1);
    xs.push_back(i2);
    xs.push_back(i3);
    xs.push_back(i4);
    return xs;
}

Intersection hit(std::vector<Intersection>& xs) {
    std::sort(xs.begin(), xs.end());
    for (auto i : xs) {
        if ((i.t > 0)) {
            return i;
        }
    }
    return Intersection(true);
}


Ray transform(Ray& r, Matrix& m) {
    Ray result(m * r.origin, m * r.direction);
    return result;
}

std::vector<Intersection> intersect(Sphere s, Ray r){
    Matrix t = inverse(s.transform);
    Ray ray = transform(r, t);
    tuple sphere_to_ray = ray.origin - point(0, 0, 0);
    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(ray.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;
    float discriminant = b*b - 4 * a * c;

    if (discriminant < 0)
        return {};
    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 > t2) std::swap(t1, t2);
    Intersection i1(t1, s);
    Intersection i2(t2, s);
    return intersections(i1, i2);
}

tuple normal_at(const Sphere &s, const tuple &world_point) {
    tuple object_point = inverse(s.transform) * world_point;
    tuple object_normal = object_point - point(0, 0, 0);
    tuple world_normal = transpose(inverse(s.transform)) * object_normal;
    world_normal.w = 0;
    return normalize(world_normal);
}

tuple reflect(tuple &in, tuple &normal) {
    return in - normal * 2 * dot(in, normal);
}

struct Computation{
    float t;
    Sphere s;
    tuple p;
    tuple eyev;
    tuple normalv;
    tuple over_point;
    bool inside;
    Computation(){}
};

Computation prepare_computations(const Intersection& i, Ray& r){
    Computation comps = Computation();
    comps.t = i.t;
    comps.s = i.s;
    comps.p = r.position(comps.t);
    comps.eyev = -r.direction;
    comps.normalv = normal_at(comps.s, comps.p);

    if (dot(comps.normalv, comps.eyev) < 0){
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } 
    else {
        comps.inside = false;
    }
    comps.over_point = comps.p + comps.normalv * EPSILON;

    return comps;
}

