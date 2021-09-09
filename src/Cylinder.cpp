#include "Cylinder.h"
#include "rt.h"

Cylinder::Cylinder() : minimum(-INFINITY), maximum(INFINITY), closed(false){}
Cylinder::Cylinder(float min, float max, bool close) : minimum(min), maximum(max), closed(close){}
std::vector<Intersection> Cylinder::local_intersect(Ray r) {
    std::vector<Intersection> xs = {};
    float a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
    if (cmp_f(a, 0)) {
        intersect_caps(r, xs);
        return xs;
    }
        
    float b = 2.0f * r.origin.x * r.direction.x + 2.0f * r.origin.z * r.direction.z;
    float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1.0f;
    float disc = b*b - 4.0f * a * c;
    if (disc < 0) return {};
    
    float t0 = (-b - std::sqrt(disc)) / (2 * a);
    float t1 = (-b + std::sqrt(disc)) / (2 * a);
    if (t0 > t1) std::swap(t0, t1);


    float y0 = r.origin.y + t0 * r.direction.y;
    if (minimum < y0 && y0 < maximum){
        xs.push_back(Intersection(t0, this));
    }

    float y1 = r.origin.y + t1 * r.direction.y;
    if (minimum < y1 && y1 < maximum){
        xs.push_back(Intersection(t1, this));
    }
    intersect_caps(r, xs);
    return xs;
}

tuple Cylinder::local_normal_at(const tuple& local_point) {
    float distance = local_point.x * local_point.x + local_point.z * local_point.z;
    if (distance < 1 && local_point.y >= maximum - EPSILON)
        return vector(0, 1, 0);
    else if (distance < 1 && local_point.y <= minimum + EPSILON)
        return vector(0, -1, 0);
    else
        return vector(local_point.x, 0, local_point.z);
}

bool Cylinder::check_cap(Ray r, float t) {
    float x = r.origin.x + t * r.direction.x;
    float z = r.origin.z + t * r.direction.z;
    float rad = x*x + z*z;
    return  (rad < 1 || cmp_f(rad, 1));
}

void Cylinder::intersect_caps(Ray r, std::vector<Intersection>& xs) {
    if (!closed || cmp_f(r.direction.y, 0)) 
        return;
    float t = (minimum - r.origin.y) / r.direction.y;
    if (check_cap(r, t)) 
        xs.push_back(Intersection(t, this));
    t = (maximum - r.origin.y) / r.direction.y;
    if (check_cap(r, t))
        xs.push_back(Intersection(t, this));
}