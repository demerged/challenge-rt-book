#include "rt.h"
#include "Light.h"
#include "Ray.cpp"
#include <algorithm>
#include <optional>

struct World {
	std::optional<Point_light> light_source;
	std::vector<Sphere> spheres;
	World(){}

	static World get_default_world(){
		World w = World();
		w.light_source = Point_light(point(-10, 10, -10), Color(1, 1, 1));
		Sphere s1 = Sphere(); Sphere s2 = Sphere();
		s1.material = Material();
		s1.material.color    = Color(0.8, 1.0, 0.6);
		s1.material.diffuse  = 0.7;
		s1.material.specular = 0.2;
		s2.set_transform(scaling(0.5, 0.5, 0.5));
		w.spheres.push_back(s1);
		w.spheres.push_back(s2);
		return w;
	}

	std::vector<Intersection> intersect_world (const Ray& r){
		std::vector<Intersection> xs;
		for (int i = 0; i < spheres.size(); i++){
			std::vector<Intersection> tmp = intersect(spheres[i], r);
			xs.insert(xs.begin(),  tmp.begin(), tmp.end());
		}
		std::sort(xs.begin(), xs.end());
		return xs;
	}
};

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

Color shade_hit(World& w, const Computation& comps){
	Point_light light;
	if (w.light_source.has_value())
		light = *w.light_source;
	bool in_shadow =  is_shadowed(w, comps.over_point);
	return lighting(comps.s.material, light, comps.p, comps.eyev, comps.normalv, in_shadow);
}

Color color_at(World& w, Ray& r){
	auto xs = w.intersect_world(r);
	Intersection i = hit(xs);
	if (i.none)
		return Color(0, 0, 0);
	Computation comps = prepare_computations(i, r);
	return shade_hit(w, comps);
}
