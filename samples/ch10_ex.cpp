#include "../rt.h"
#include "../matrix.h"
#include "../Ray.cpp"
#include "../World.cpp"
#include "../Light.h"
#include "../Camera.cpp"
#include "../Sphere.cpp"
#include "../Plane.cpp"
#include "../Stripe_pattern.cpp"
#include "../Gradient_pattern.cpp"
#include "../Ring_pattern.cpp"
#include "../Checker_pattern.cpp"
#include "../Experimental_pattern.cpp"

int main() {
    World w = World();
    w.light_source = Point_light(point(0, 10, 5), Color(1, 1, 1));
    
    auto floor = std::make_shared<Plane>();
    floor->set_transform(translation(0, -1, 0) * scaling(10, 0.05, 10));
    floor->material.transparency = 0.5;
    floor->material.refractive_index = 1.5;
    Checker_pattern gp(Color(1,1,1), Color(0,0,0));
    gp.set_transform(scaling(0.05, 0.05, 0.05));
    floor->material.pattern = &gp;
    
    auto ball = std::make_shared<Sphere>();
    ball->set_transform(translation(0, 3.5, 0) * scaling(0.5, 0.5, 0.5));
    ball->material.transparency = 1.0;
    ball->material.reflective= 1.0;
    ball->material.refractive_index = 1.1;
    ball->material.diffuse = 0.1;

    auto ball2 = std::make_shared<Sphere>();
    ball2->set_transform(translation(0, 3.5, 0));
    ball2->material.transparency = 1.0;
    ball2->material.reflective= 1.0;
    ball2->material.refractive_index = 1.5;
    ball2->material.diffuse = 0.1;


    w.shapes.push_back(floor);
    w.shapes.push_back(ball);
    w.shapes.push_back(ball2);

    
        
    Camera cam = Camera(2000, 2000, PI/3.0);
    cam.set_transform(view_transform(point(0, 10, 0), point(0, 0, 0),vector(0, 0, 1)));
    Canvas image = render(cam, w);
    canvas_to_ppm(image, "out.ppm");
    

}