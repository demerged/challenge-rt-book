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



int main(){
    std::shared_ptr<Shape> floor = std::make_shared<Plane>();
    floor->set_transform(scaling(10, 0.05, 10));
    floor->material = Material();
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    Checker_pattern gp(Color(1,1,1), Color(0.2, 0.7, 0.7));
    floor->material.pattern = &gp;
    floor->material.pattern->set_transform(scaling(0.15, 0.15, 0.15));
        
    
    std::shared_ptr<Shape> back_drop = std::make_shared<Plane>();
    back_drop->set_transform(translation(0, 0, 10) * rotation_x(PI/2) * scaling(10, 0.01, 10));
    back_drop->material = Material();
    back_drop->material.color = Color(0.63, 0.69, 0.75);
    back_drop->material.diffuse = 0.8;
    back_drop->material.specular = 0.;
    Gradient_pattern cp(Color(0.968, 0.568, 0.078), Color(0.609, 0.968, 0.078));
    cp.set_transform(rotation_y(PI/2) * scaling(1, 1, 5));
    back_drop->material.pattern = &cp;


    

    std::shared_ptr<Shape> middle = std::make_shared<Sphere>();
    middle->set_transform(translation(-0.5, 1, 0.5));
    middle->material = Material();
    middle->material.color = Color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    //std::shared_ptr<Pattern> p = std::make_shared<Stripe_pattern>(Color(1, 1, 1), Color(0.9, 0.3, 0.3));
    // Pattern p = stripe_pattern(Color(1, 1, 1), Color(0.9, 0.3, 0.3));
    //Stripe_pattern p(Color(1, 1, 1), Color(0.9, 0.3, 0.3));
    Checker_pattern p(Color(1, 1, 1), Color(0.9, 0.3, 0.3));
    middle->material.pattern = &p;
    //middle->material.pattern->set_transform(rotation_z(PI/1.3) * scaling(0.125, 1, 1));
    middle->material.pattern->set_transform(scaling(0.25, 0.25, 0.25));

    std::shared_ptr<Shape> right = std::make_shared<Sphere>();
    right->set_transform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right->material = Material();
    right->material.color = Color(0.1, 1, 0.5);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    Ring_pattern rp(Color(0.16, 0.794, 0.2),Color(0, 0.477, 0.31));
    rp.set_transform(rotation_y(PI/1.2) * scaling(0.1, 1, 1));
    right->material.pattern = &rp;

    
    

    std::shared_ptr<Shape> left = std::make_shared<Sphere>();
    left->set_transform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left->material = Material();
    left->material.color = Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    Gradient_pattern gpleft(Color(1, 0, 0), Color(0, 1, 0));
    gpleft.set_transform(translation(-0.9, 0, 0) * scaling(2, 1, 1));
    left->material.pattern = &gpleft;
    
    World world = World();
    world.shapes.push_back(floor);
    world.shapes.push_back(back_drop);
    world.shapes.push_back(middle);
    world.shapes.push_back(left);
    world.shapes.push_back(right);
    world.light_source = Point_light(point(-10, 10, -10), Color(1, 1, 1));
    Camera cam = Camera(5000, 5000, PI/3.0f);
    cam.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0),vector(0, 1, 0)));
    // cam.set_transform(view_transform(point(0, 10, 0), point(0, 0, 0),vector(0, 0, 1)));
    // cam.set_transform(view_transform(point(5, 1, -5), point(-5, 3, 5),vector(0, 1, 0)));
    Canvas canvas = render(cam, world);
    canvas_to_ppm(canvas);
}
