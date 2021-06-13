#include "../rt.h"
#include "../matrix.h"
#include "../Ray.cpp"
#include "../World.cpp"
#include "../Light.h"
#include "../Camera.cpp"


int main(){
    Sphere floor = Sphere();
    floor.transform = scaling(10, 0.01, 10);
    floor.material = Material();
    floor.material.color = Color(1, 0.9, 0.9);
    floor.material.specular = 0;

    Sphere left_wall = Sphere();
    left_wall.transform = translation(0, 0, 5) *
                            rotation_y(-PI/4.0f) *
                            rotation_x(PI/2) *
                            scaling(10, 0.01, 10);
    left_wall.material = floor.material;

    Sphere right_wall = Sphere();
    right_wall.transform = translation(0, 0, 5) *
                            rotation_y(PI/4.0f) *
                            rotation_x(PI/2) *
                            scaling(10, 0.01, 10);
    right_wall.material = floor.material;

    Sphere middle = Sphere();
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = Material();
    middle.material.color = Color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    Sphere right = Sphere();
    right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right.material = Material();
    right.material.color = Color(0.1, 1, 0.5);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    
    Sphere left = Sphere();
    left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left.material = Material();
    left.material.color = Color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    
    World world = World();
    world.spheres.push_back(floor);
    world.spheres.push_back(left_wall);
    world.spheres.push_back(right_wall);
    world.spheres.push_back(middle);
    world.spheres.push_back(left);
    world.spheres.push_back(right);
    world.light_source = Point_light(point(-10, 10, -10), Color(1, 1, 1));
    Camera cam = Camera(800, 600, PI/3.0f);
    cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0),vector(0, 1, 0));
    Canvas canvas = render(cam, world);
    canvas_to_ppm(canvas);
}