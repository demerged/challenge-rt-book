#include "../rt.h"
#include "../Matrix.h"
#include "../Ray.h"
#include "../World.h"
#include "../Light.h"
#include "../Camera.h"
#include "../Sphere.h"

int main() {
	float wall_z = 10.f;
	float wall_size = 7.0f;
	int canvas_pixels = 20;
	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;
	Canvas c(canvas_pixels, canvas_pixels);
	Color const red(1.f, 0.f, 0.f);
	Color const black(0.f, 0.f, 0.f);
	Color const white(1.f, 1.f, 1.f);
	Sphere s = Sphere();
	s.material.color = Color(1, 0.2, 1);

	Point_light light = Point_light(point(-10, 10, -10), Color(1, 1, 1));

	//s.set_transform(rotation_z(PI / 4) * scaling(1.f, 0.5f, 1.f));
	tuple origin = point(0, 0, -5.f);
	for (int y = 0; y < canvas_pixels; y++) {
		float world_y = half - pixel_size * (float)y;
		for (int x = 0; x < canvas_pixels; x++) {
			float world_x = -half + pixel_size * (float)x;

			tuple direction = point(world_x, world_y, wall_z) - origin;
			Ray ray = Ray(origin, normalize(direction));
			auto xs = s.intersect(ray);
			Intersection is = hit(xs);

			tuple p = ray.position(is.t);
			tuple normal = is.s->normal_at(p);
			tuple eye = -ray.direction;
			Color color = lighting(is.s->material, is.s, light, p, eye, normal, false);

			if (!is.none)
				write_pixel(c, x, y, color);
		}
	}
	canvas_to_ppm(c, "out.ppm");
}
