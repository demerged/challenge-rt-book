#include "Cube.h"

struct tpair {
    float tmin, tmax;
};

std::vector<Intersection> Cube::local_intersect(Ray r) {
    tpair x = check_axis(r.origin.x, r.direction.x);
    tpair y = check_axis(r.origin.y, r.direction.y);
    tpair z = check_axis(r.origin.z, r.direction.z);

    float tmin = std::max(x.tmin, std::max(y.tmin, z.tmin));
    float tmax = std::min(x.tmax, std::min(y.tmax, z.tmax));

    if (tmin > tmax) return {};

    return { Intersection(tmin, this), Intersection(tmax, this) };
}
tuple Cube::local_normal_at(const tuple& local_point) {
    float maxc = std::max({std::abs(local_point.x), std::abs(local_point.y),
        std::abs(local_point.z)});
    if (maxc == std::abs(local_point.x)){
        return vector(local_point.x, 0, 0);
    } else if (maxc == std::abs(local_point.y)) {
        return vector(0, local_point.y, 0);
    }

    return vector(0, 0, local_point.z);
}

tpair check_axis(float origin, float direction) {
    float tmin_numerator = (-1 - origin);
    float tmax_numerator = (1 - origin);
    float tmin, tmax;
    if (std::fabs(direction) >= EPSILON) {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    } else {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax) std::swap(tmin, tmax);

    return tpair{tmin, tmax};
}
