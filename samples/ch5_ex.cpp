#include "../Ray.cpp"

int main() {
	float wall_z = 10.f;
	float wall_size = 7.0f;
	int canvas_pixels = 400;
	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;
	Canvas c(canvas_pixels, canvas_pixels);
	Color const red(1.f, 0.f, 0.f);
	Color const black(0.f, 0.f, 0.f);
	Color const white(1.f, 1.f, 1.f);
	Sphere s = Sphere();
	s.set_transform(rotation_z(PI/4) * scaling(1.f, 0.5f, 1.f));
	tuple origin = point(0, 0, -5.f);
	for (int y = 0; y < canvas_pixels; y++) {
		float world_y = half - pixel_size * (float)y;
		for (int x = 0; x < canvas_pixels; x++) {
			float world_x = -half + pixel_size * (float)x;

			tuple direction = point(world_x, world_y, wall_z) - origin;
			Ray ray = Ray(origin, normalize(direction));
			auto xs = intersect(s, ray);
			Intersection is = hit(xs);

			if (!is.none)
				write_pixel(c, x, y, red);
		}
	}
	canvas_to_ppm(c);


}