#include "World.h"

World::World(){}

World World::get_default_world(){
    World w = World();
    w.light_source = Point_light(point(-10, 10, -10), Color(1, 1, 1));
    std::shared_ptr<Shape> s1 = std::make_shared<Sphere>(); std::shared_ptr<Shape> s2 = std::make_shared<Sphere>();

    s1->material = Material();
    s1->material.color    = Color(0.8, 1.0, 0.6);
    s1->material.diffuse  = 0.7;
    s1->material.specular = 0.2;
    s2->set_transform(scaling(0.5, 0.5, 0.5));
    w.shapes.push_back(s1);
    w.shapes.push_back(s2);
    return w;
}

std::vector<Intersection> World::intersect_world (const Ray& r){
    std::vector<Intersection> xs;
    for (int i = 0; i < shapes.size(); i++){
        std::vector<Intersection> tmp =  shapes[i]->intersect(r);
        xs.insert(xs.begin(),  tmp.begin(), tmp.end());
    }
    std::sort(xs.begin(), xs.end());
    return xs;
}

bool is_shadowed(World& w, tuple p){
    Point_light plight;
    if (w.light_source.has_value())
        plight = *w.light_source;
    tuple v = plight.position - p;
    float distance = magnitude(v);
    tuple direction = normalize(v);
    Ray r = Ray(p, direction);
    auto xs = w.intersect_world(r);
    Intersection h = hit(xs);
    return (!h.none && h.t < distance);
}

Color shade_hit(World& w, const Computation& comps, int remaining){
    Point_light light;
    if (w.light_source.has_value())
        light = *w.light_source;
    bool in_shadow =  is_shadowed(w, comps.over_point);
    Color surface = lighting(comps.s->material, comps.s, light, comps.over_point, comps.eyev, comps.normalv, in_shadow);
    Color reflected = reflected_color(w, comps, remaining);
    Color refracted = refracted_color(w, comps, remaining);

    Material* material = &comps.s->material;
    if (material->reflective > 0 && material->transparency > 0){
        float reflectance = Schlick(comps);
        return surface + reflected * reflectance +
                        refracted * (1 - reflectance);
    }
    else
        return surface + reflected + refracted;
}

Color color_at(World& w, Ray& r, int remaining){
    auto xs = w.intersect_world(r);
    Intersection i = hit(xs);
    if (i.none)
        return Color(0, 0, 0);
    Computation comps = prepare_computations(i, r, xs);
    return shade_hit(w, comps, remaining);
}

Color reflected_color(World& w, const Computation& comps, int remaining){
    if (cmp_f(comps.s->material.reflective, 0) || remaining < 0 || cmp_f(remaining, 0)) {
        return Color(0, 0, 0);
    }
    Ray reflect_ray = Ray(comps.over_point, comps.reflectv);
    Color color = color_at(w, reflect_ray, remaining-1);
    return color * comps.s->material.reflective;
}

Color refracted_color(World& w, const Computation& comps, int remaining){
    if (cmp_f(comps.s->material.transparency, 0) || remaining < 0 || cmp_f(remaining, 0))
        return Color(0, 0, 0);

    float n_ratio = comps.n1 / comps.n2;
    float cos_i = dot(comps.eyev, comps.normalv);
    float sin2_t = n_ratio*n_ratio * (1.0 - cos_i*cos_i);
    if (sin2_t > 1)
        return Color(0, 0, 0);

    float cos_t = std::sqrt(1.0 - sin2_t);
    tuple direction = comps.normalv * (n_ratio * cos_i - cos_t) -
                        comps.eyev * n_ratio;

    Ray refract_ray = Ray(comps.under_point, direction);
    Color color = color_at(w, refract_ray, remaining-1) * comps.s->material.transparency;

    return color;
}

float Schlick(const Computation& comps){
    float cos = dot(comps.eyev, comps.normalv);
    if (comps.n1 > comps.n2){
        float n_ratio = comps.n1 / comps.n2;
        float sin2_t = n_ratio*n_ratio * (1.0 - cos*cos);
        if (sin2_t > 1.0) return 1.0;

        float cos_t = std::sqrt(1.0 - sin2_t);
        cos = cos_t;
    }

    float r0 = std::pow(((comps.n1 - comps.n2) / (comps.n1 + comps.n2)), 2);
    return r0 + (1.0 - r0) * std::pow((1 - cos), 5);
}
