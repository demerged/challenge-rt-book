#pragma once
#include "rt.h"

struct Material {
	Color color;
	float ambient, diffuse, specular, shininess;

	Material() {
		color = Color(1, 1, 1);
		ambient = 0.1;
		diffuse = 0.9;
		specular = 0.9;
		shininess = 200.0;
	}

	bool operator==(const Material& m) const {
		return (color == m.color) &&
			(cmp_f(ambient, m.ambient)) &&
			(cmp_f(diffuse, m.diffuse)) &&
			(cmp_f(specular, m.specular)) &&
			(cmp_f(shininess, m.shininess));
	}
};