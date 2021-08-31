#pragma once
#include "rt.h"
#include "Material.h"
#include "Ray.h"
#include "Pattern.h"

struct Point_light {
	Color intensity;
	tuple position;
	Point_light();
	Point_light(const tuple& pos, const Color& intense);
};

Color lighting(const Material &material, Shape* object, Point_light &light,
		const tuple point, tuple eyev, tuple normalv, bool in_shadow);
