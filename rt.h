#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define PI 3.14159
#define EPSILON 0.001

bool cmp_f(float a, float b);

struct tuple {
    float x, y, z, w;
    tuple();
    tuple(float xx, float yy, float zz, float ww);

    bool operator==(const tuple &t) const;
    tuple operator+(const tuple &t) const;
    tuple operator-(const tuple &t) const;
    tuple operator-() const;
    tuple operator*(float a) const;
    tuple operator/(float a) const;

    friend std::ostream &operator<<(std::ostream &os, const tuple &t);
};

struct Color{
    float red, green, blue;
    Color();
    Color(float r, float g, float b);

    Color operator+(const Color &c);
    Color operator-(const Color &c);
    Color operator*(const Color &c) const;
    Color operator*(float scale);
    bool operator==(const Color &c) const;
    friend std::ostream &operator<<(std::ostream& os, const Color& c);
};

Color hadamard_product(const Color &c1, const Color &c2);

struct Canvas{
    int width;
    int height;
    std::vector<std::vector<Color>> canvas;
    //Color** canvas = new Color*[width];
    Canvas(int w, int h);
};

tuple color(float r, float g, float b);

tuple point(float x, float y, float z);

tuple vector(float x, float y, float z);

float magnitude(const tuple &t);

tuple normalize(const tuple &t);

float dot(const tuple &a, const tuple &b);

tuple cross(tuple &a, tuple &b);

void write_pixel(Canvas &c, int x, int y, const Color &color);
Color pixel_at(const Canvas  &c, int x, int y);
int convert_to_pixel(float value);
void canvas_to_ppm(const Canvas &c, const std::string& file_name);
/*
int main(){
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();
    std::cout<< cross(vector(1,0,0), vector(0, 1, 0)) << std::endl;
}
*/
