#include "rt.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"
#include "Light.h"
#include "Camera.h"
#include "Sphere.h"


int main(){
    std::shared_ptr<Shape> floor = std::make_shared<Sphere>();
    floor->transform = scaling(10, 0.01, 10);
    floor->material = Material();
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;

    std::shared_ptr<Shape> left_wall = std::make_shared<Sphere>();
    left_wall->transform = translation(0, 0, 5) *
                            rotation_y(-PI/4.0f) *
                            rotation_x(PI/2) *
                            scaling(10, 0.01, 10);
    left_wall->material = floor->material;

    std::shared_ptr<Shape> right_wall = std::make_shared<Sphere>();
    right_wall->transform = translation(0, 0, 5) *
                            rotation_y(PI/4.0f) *
                            rotation_x(PI/2) *
                            scaling(10, 0.01, 10);
    right_wall->material = floor->material;

    std::shared_ptr<Shape> middle = std::make_shared<Sphere>();
    middle->transform = translation(-0.5, 1, 0.5);
    middle->material = Material();
    middle->material.color = Color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;

    std::shared_ptr<Shape> right = std::make_shared<Sphere>();
    right->transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right->material = Material();
    right->material.color = Color(0.1, 1, 0.5);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;

    std::shared_ptr<Shape> left = std::make_shared<Sphere>();
    left->transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left->material = Material();
    left->material.color = Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    
    World world = World();
    world.shapes.push_back(floor);
    world.shapes.push_back(left_wall);
    world.shapes.push_back(right_wall);
    world.shapes.push_back(middle);
    world.shapes.push_back(left);
    world.shapes.push_back(right);
    world.light_source = Point_light(point(-10, 10, -10), Color(1, 1, 1));
    Camera cam = Camera(800, 600, PI/3.0f);
    cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0),vector(0, 1, 0));
    Canvas canvas = render(cam, world);
    canvas_to_ppm(canvas, "out.ppm");
}
