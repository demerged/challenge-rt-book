#pragma once
#include <cmath>
#include <thread>
#include "Matrix.h"
#include "Ray.h"
#include "World.h"

#define MULTI_THREAD 1

//int current;

struct Camera{
    int hsize, vsize;
    float fov;
    float pixel_size;
    float half_view, aspect, half_width, half_height;
    Matrix transform = Matrix(4);
    Matrix inversed_transform = Matrix(4);
    Camera();
    Camera(int hs, int vs, float fv);

    Ray ray_for_pixel(int px, int py);

    void set_transform(const Matrix& mat);
};

void render_thread(Canvas *image, Camera *cam, World *w, const int &mod);

Canvas render(Camera& cam, World& world);


