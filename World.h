#pragma once
#include <memory>
#include "rt.h"
#include "Light.h"
#include "Ray.h"
#include <algorithm>
#include <optional>
#include "Shape.h"
#include "Sphere.h"
#include "Computation.h"

struct World {
	std::optional<Point_light> light_source;
	std::vector<std::shared_ptr<Shape>> shapes;
	World();

	static World get_default_world();

	std::vector<Intersection> intersect_world (const Ray& r);
};

bool is_shadowed(World& w, tuple p);


Color reflected_color(World& w, const Computation& comps, int remaining); 

float Schlick(const Computation& comps);

Color shade_hit(World& w, const Computation& comps, int remaining);

Color color_at(World& w, Ray& r, int remaining=5);

Color refracted_color(World& w, const Computation& comps, int remaining);
float Schlick(const Computation& comps);