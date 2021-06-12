#include <cmath>

struct Camera{
    int hsize, vsize;
    float fov;
    float pixel_size;
    float half_view, aspect, half_width, half_height;
    Matrix transform = Matrix(4);
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
            };

    Ray ray_for_pixel(int px, int py){
        float xoffset = (px + 0.5) * pixel_size;
        float yoffset = (py + 0.5) * pixel_size;

        float world_x = half_width  - xoffset;
        float world_y = half_height - yoffset;

        tuple pixel = inverse(transform) * point(world_x, world_y, -1);
        tuple origin = inverse(transform) * point(0, 0, 0);
        tuple direction = normalize(pixel - origin);

        return Ray(origin, direction);
    }
};

Canvas render(Camera& cam, World& world){
    Canvas image = Canvas(cam.hsize, cam.vsize);
    for (int y = 0; y < cam.vsize; y++){
        for (int x = 0; x < cam.hsize; x++){
            Ray ray = cam.ray_for_pixel(x, y);
            Color color = color_at(world, ray);
            write_pixel(image, x, y, color);
        }
    }
    return image;
}
