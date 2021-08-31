#pragma once
#include <vector>
#include <algorithm>
#include "rt.h"

struct Shape;
struct Sphere;

struct Intersection{
    float t;
    Shape* s;
    bool none;
    Intersection(float t_, Shape* s_);
    Intersection(bool n);

    bool operator<(const Intersection& i) const;
    bool operator==(const Intersection& i) const;
};


std::vector<Intersection> intersections(Intersection i1, Intersection i2);

std::vector<Intersection> intersections(Intersection i1, Intersection i2, Intersection i3);

std::vector<Intersection> intersections(Intersection i1, Intersection i2, Intersection i3, Intersection i4);

Intersection hit(std::vector<Intersection>& xs);
