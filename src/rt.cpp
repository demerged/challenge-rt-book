#include "rt.h"

bool cmp_f(float a, float b) {
    return (std::fabs(a - b) < EPSILON);
}

tuple::tuple() {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
}

tuple::tuple(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww) {};
bool tuple::operator==(const tuple &t) const {
    return (cmp_f(x, t.x) && cmp_f(y, t.y) && cmp_f(z, t.z) && cmp_f(w, t.w));
}
tuple tuple::operator+(const tuple &t) const {
    return tuple(x+t.x, y+t.y, z+t.z, w+t.w);
}
tuple tuple::operator-(const tuple &t) const {
    return tuple(x-t.x, y-t.y, z-t.z, w-t.w);
}
tuple tuple::operator-() const {
    return tuple(-x, -y, -z, -w);
}
tuple tuple::operator*(float a) const {
    return tuple(x*a, y*a, z*a, w*a);
}
tuple tuple::operator/(float a) const {
    return tuple(x/a, y/a, z/a, w/a);
}
std::ostream &operator<<(std::ostream &os, const tuple &t){
    if (t.w == 0) os << "vector";
    else if (t.w == 1) os << "point";
    else os << "tuple";
    return os << "(" << t.x << ", " << t.y << ", " << t.z << ", " << t.w << ")";
}



Color::Color(): red(0.0), green(0.0), blue(0.0) {};
Color::Color(float r, float g, float b): red(r), green(g), blue(b) {};

Color Color::operator+(const Color &c) {
    return Color(red+c.red, green+c.green, blue+c.blue);
}
Color Color::operator-(const Color &c) {
    return Color(red-c.red, green-c.green, blue-c.blue);
}
Color Color::operator*(const Color &c) const{
    return Color(red*c.red, green*c.green, blue*c.blue);
}
Color Color::operator*(float scale) {
    return Color(red*scale, green*scale, blue*scale);
}
bool Color::operator==(const Color &c) const {
    return (cmp_f(red, c.red) && cmp_f(green, c.green) && cmp_f(blue, c.blue));
}
std::ostream &operator<<(std::ostream& os, const Color& c){
    return os << "Color(" << c.red << ", " << c.green << ", " << c.blue << ")";
}

Color hadamard_product(const Color &c1, const Color &c2) {
    return (c1*c2);
}

Canvas::Canvas(int w, int h): width(w), height(h) {
    //canvas.resize(height, std::vector<Color>(width) );
    for (int i = 0; i < height; i++){
        std::vector<Color> row;
        for (int j = 0; j < width; j++){
            row.push_back(Color(0, 0, 0));
        }
        canvas.push_back(row);
    }
}


tuple color(float r, float g, float b) {
    return tuple(r, g, b, 0);
}

tuple point(float x, float y, float z) {
    return tuple(x, y, z, 1);
}

tuple vector(float x, float y, float z) {
    return tuple(x, y, z, 0);
}

float magnitude(const tuple &t){
    return sqrt(t.x*t.x + t.y*t.y + t.z*t.z + t.w*t.w);
}

tuple normalize(const tuple &t){
    float norm = magnitude(t);
    return tuple(t.x / norm,
                 t.y / norm,
                 t.z / norm,
                 t.w / norm);
}

float dot(const tuple &a, const tuple &b){
    return a.x * b.x +
           a.y * b.y +
           a.z * b.z +
           a.w * b.w;
}

tuple cross(tuple &a, tuple &b){
    return vector(a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}

void write_pixel(Canvas &c, int x, int y, const Color &color){
    if (y < 0) return;
    if (x < 0) return;
    if (y >= c.height) return;
    if (x >= c.width) return;
    //std::cout << x << " " << y << std::endl;
    c.canvas[y][x] = color;
}
Color pixel_at(const Canvas  &c, int x, int y){
    return c.canvas[y][x];
}
int convert_to_pixel(float value){
    float new_value = 0 + (value - 0) * (255 - 0) / (1 - 0);
    if (new_value > 255) new_value = 255;
    else if (new_value < 0) new_value = 0;
    return roundf(new_value);
}
void canvas_to_ppm(const Canvas &c, const std::string& file_name){
    std::stringstream ss;
    std::ofstream outFile(file_name);
    ss << "P3\n";
    ss << c.width << " " << c.height << "\n";
    ss << "255\n";
    int r, g, b;
    for (int i = 0; i < c.height; i++){
        for (int j = 0; j < c.width; j++) {
            r = convert_to_pixel(c.canvas[i][j].red);
            g = convert_to_pixel(c.canvas[i][j].green);
            b = convert_to_pixel(c.canvas[i][j].blue);
            ss << r << " ";
            ss << g << " ";
            ss << b << "\n";
        }
    }
    outFile << ss.str();
}
/*
int main(){
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();
    std::cout<< cross(vector(1,0,0), vector(0, 1, 0)) << std::endl;
}
*/
