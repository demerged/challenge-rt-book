#include "Intersection.h"


Intersection::Intersection(float t_, Shape* s_) : t(t_), s(s_) { none = false; };
Intersection::Intersection(bool n) { t = 0.0; s = nullptr; none = true; }

bool Intersection::operator<(const Intersection& i) const {
    return (t < i.t);
}

bool Intersection::operator==(const Intersection& i) const{
    return (cmp_f(t, i.t)) && (s == i.s);
}

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

