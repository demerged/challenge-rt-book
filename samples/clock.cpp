#include "Matrix.h"

int main(){
    Canvas c(400, 400);
    Color const white(1.f, 1.f, 1.f);
    float const rotationAngle = PI / 6.f;
    Matrix translate = translation(200.f, 200.f, 0.f);
    Matrix scale = scaling(150.f, 150.f, 1.f);
    Matrix tx = translate * scale;

    // Draw clock center
    write_pixel(c, 200, 200, Color(1.f, 0.f, 0.f));

    tuple twelveOclock = point(0.f, 1.f, 0.f);
    for (auto h : { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 })
    {
        Matrix rotate = rotation_z((h) * -rotationAngle);

        tuple actualHour = tx * rotate * twelveOclock;
        write_pixel(c, (uint32_t)actualHour.x, c.height - (uint32_t)actualHour.y, white);
    }

    canvas_to_ppm(c, "out.ppm");

    return 0;
}
