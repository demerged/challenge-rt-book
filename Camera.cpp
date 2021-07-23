#include <cmath>
#include <thread>
#include "matrix.h"
#include "Ray.cpp"
#include "World.cpp"

#define MULTI_THREAD 1

int current = 0;

struct Camera{
    int hsize, vsize;
    float fov;
    float pixel_size;
    float half_view, aspect, half_width, half_height;
    Matrix transform = Matrix(4);
    Matrix inversed_transform = Matrix(4);
    Camera(int hs, int vs, float fv)
            : hsize(hs)
            , vsize(vs)
            , fov(fv)
            {
                half_view = tan(fov / 2.0f);
                aspect = (float) hsize / vsize;
                if (aspect >= 1){
                    half_width = half_view;
                    half_height = half_view / aspect;
                } else {
                    half_width = half_view * aspect;
                    half_height = half_view;
                }
                pixel_size = (half_width * 2) / hsize;

                transform = Matrix::get_identity();
                inversed_transform = Matrix::get_identity();
            };

    Ray ray_for_pixel(int px, int py){
        float xoffset = (px + 0.5) * pixel_size;
        float yoffset = (py + 0.5) * pixel_size;

        float world_x = half_width  - xoffset;
        float world_y = half_height - yoffset;

        tuple pixel = inversed_transform * point(world_x, world_y, -1);
        tuple origin = inversed_transform * point(0, 0, 0);
        tuple direction = normalize(pixel - origin);

        return Ray(origin, direction);
    }

    void set_transform(const Matrix& mat){
        transform = mat;
        inversed_transform = inverse(transform);
    }
};

void render_thread(Canvas *image, Camera *cam, World *w, const int &mod) {
  for (int y = 0; y < cam->vsize; ++y) {
    if (y % std::thread::hardware_concurrency() != mod) {
      continue;
    }
    for (int x = 0; x < cam->hsize; ++x){
      Ray r = cam->ray_for_pixel(x, y);
      Color c = color_at(*w, r);
      write_pixel(*image, x, y, c);
    }
    //std::cout << "\rProgress: " << (y * 100) / cam->vsize << "%" << std::flush;
    if (current < y+1) {
        current = y+1;
        std::cout << "\rLine: " << current << "/" << cam->vsize  << "\t" << std::flush;
    }
  }
}

Canvas render(Camera& cam, World& world){

#if MULTI_THREAD
    std::cout << "Rendering with " << std::thread::hardware_concurrency()
    << " threads." << std::endl;
    Canvas image = Canvas(cam.hsize, cam.vsize);
    std::vector<std::thread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        std::thread thread(&render_thread, &image, &cam, &world, i);
        threads.push_back(std::move(thread));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << "\n"; 
    return image;
#else
    std::cout << "Rendering with 1 thread" << std::endl;
    Canvas image = Canvas(cam.hsize, cam.vsize);
    for (int y = 0; y < cam.vsize; y++){
        for (int x = 0; x < cam.hsize; x++){
            Ray ray = cam.ray_for_pixel(x, y);
            Color color = color_at(world, ray);
            write_pixel(image, x, y, color);
        }
        //std::cout << "\rProgress: " << (y * 100) / cam.vsize << "%" << std::flush;
        std::cout << "\rLine: " << y+1 << "/" << cam.vsize << std::flush;
    }
    std::cout << "\nDone!" << std::endl;
    return image;

#endif
}


