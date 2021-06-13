#pragma once
#include "rt.h"
#include "Material.h"
#include "Ray.cpp"

struct Point_light {
	Color intensity;
	tuple position;
	Point_light(){}
	Point_light(const tuple& pos, const Color& intense) : position(pos), intensity(intense) {};
};

Color lighting(const Material &material, Point_light &light, 
			   const tuple point, tuple eyev, tuple normalv, bool in_shadow) {
	Color black = Color(0.0f, 0.0f, 0.0f);
	Color ambient, diffuse, specular;
	Color effective_color = material.color * light.intensity;
	tuple lightv = normalize(light.position - point);
	ambient = effective_color * material.ambient;
	float light_dot_normal = dot(lightv, normalv);

	if (light_dot_normal < 0 || in_shadow) {
		diffuse = black;
		specular = black;
	}
	else{
		diffuse = effective_color * material.diffuse * light_dot_normal;
		tuple neg_lightv = -lightv;
		tuple reflectv = reflect(neg_lightv, normalv);
		float reflect_dot_eye = dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = black;
		else {
			float factor = pow(reflect_dot_eye, material.shininess);
			specular = light.intensity * material.specular * factor;
		}
	}

	return ambient + diffuse + specular;
}
