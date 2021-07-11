#pragma once
#include "rt.h"
#include "Ray.cpp"
#include "Sphere.cpp"

struct Computation{
    float t;
    Shape* s;
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
    comps.normalv = comps.s->normal_at(comps.p);

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

