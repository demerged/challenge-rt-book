#include "rt.h"
#include "Matrix.h"
#include "Ray.h"
#include "World.h"
#include "Light.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Stripe_pattern.h"
#include "Gradient_pattern.h"
#include "Ring_pattern.h"
#include "Checker_pattern.h"
#include "Experimental_pattern.h"

int main() {
    World w = World();
    w.light_source = Point_light(point(0, 10, 5), Color(1, 1, 1));
    
    std::shared_ptr<Shape> floor = std::make_shared<Plane>();
    floor->set_transform(scaling(10, 0.05, 10));
    floor->material = Material();
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    floor->material.reflective = 0.0;
    floor->material.diffuse= 0.5;
    Checker_pattern gp(Color(1,1,1), Color(0.2, 0.7, 0.7));
    floor->material.pattern = &gp;
    floor->material.pattern->set_transform(scaling(0.15, 0.15, 0.15));
    
    std::shared_ptr<Shape> left = std::make_shared<Plane>();
    std::shared_ptr<Shape> right = std::make_shared<Plane>();

    left->material.reflective = 1.0;
    left->set_transform(translation(-2, 1, 0) * rotation_z(PI/2.0) * scaling(0.01, 0.05, 0.01));

    right->material.reflective = 1.0;
    right->material.transparency = 0.9;
    right->material.diffuse = 0.2;
    right->material.specular = 1.0;
    right->material.shininess = 300;
    right->set_transform(translation(2, 1, 0) * rotation_z(PI/2.0) * scaling(0.01, 0.05, 0.01));



    std::shared_ptr<Shape> ball = std::make_shared<Sphere>();
    ball->material.color = Color(0.234, 0.123, 0.312);
    ball->set_transform(translation(0, 1, 0));


    w.shapes.push_back(floor);
    w.shapes.push_back(left);
    w.shapes.push_back(right);
    w.shapes.push_back(ball);
    
    
    Camera cam = Camera(4096, 3256, PI/2.0);
    cam.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0),vector(0, 1, 0)));
    Canvas image = render(cam, w);
    canvas_to_ppm(image, "out.ppm");
    

}