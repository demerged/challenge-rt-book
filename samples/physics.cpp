#include "rt.h"
#include <sstream>

struct Projectile {
    tuple pos;
    tuple velocity;
    Projectile(tuple pos_, tuple vel_): pos(pos_), velocity(vel_) {};
};

struct Environment {
    tuple gravity;
    tuple wind;
    Environment(tuple grav_, tuple wind_): gravity(grav_), wind(wind_) {};
};

Projectile tick(Projectile &proj, Environment &env){
    tuple new_pos = proj.pos + proj.velocity;
    tuple velocity = proj.velocity + env.gravity + env.wind;
    return Projectile(new_pos, velocity);
}

int main(){
    Projectile p = Projectile(point(0, 1, 0), normalize(vector(1.0, 1.8, 0)) * 11.25);
    Environment e = Environment(vector(0, -0.1, 0), vector(-0.01, 0, 0));
    Canvas c(900, 500);

     while (p.pos.y >= 0){
        p = tick(p, e);
        //std::cout << p.pos.x << " " << c.height - p.pos.y << std::endl;
        write_pixel(c, roundf(p.pos.x), roundf(c.height - p.pos.y), Color(1, 0, 0));
    }

    canvas_to_ppm(c, "out.ppm");
}