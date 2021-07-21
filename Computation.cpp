#pragma once
#include <algorithm>
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
    tuple under_point;
    tuple reflectv;
    bool inside;
    float n1, n2;
    Computation(){}
};

Computation prepare_computations(const Intersection& i, Ray& r, const std::vector<Intersection>& xs = {}){
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
    comps.over_point  = comps.p + comps.normalv * EPSILON;
    comps.under_point = comps.p - comps.normalv * EPSILON;

    comps.reflectv = reflect(r.direction, comps.normalv);


    std::vector<Shape*> containers;
    for (size_t j = 0; j < xs.size(); ++j){
        if (i == xs[j]) {
            if (containers.empty())
                comps.n1 = 1.0;
            else{
                comps.n1 = containers.back()->material.refractive_index;
            }
        }

        auto it = std::find(containers.begin(), containers.end(), xs[j].s);
        if(it != containers.end()) {
            containers.erase(it);
        } else {
            containers.push_back(xs[j].s);
        }

        if (i == xs[j]){
            if (containers.empty())
                comps.n2 = 1.0;
            else{
                comps.n2 = containers.back()->material.refractive_index;
                break;
            }
        }
        
    }

    return comps;
}

