#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include "rt.h"
#include "matrix.h"
#include "Ray.cpp"
#include "Light.h"
#include "Material.h"
#include "World.cpp"
#include "Camera.cpp"
#include "Intersection.cpp"
#include "Computation.cpp"
#include "Shape.cpp"
#include "Sphere.cpp"
#include "Plane.cpp"
#include "Stripe_pattern.cpp"
#include "Gradient_pattern.cpp"
#include "Ring_pattern.cpp"
#include "Checker_pattern.cpp"

TEST(AppTest, PointTest){
    EXPECT_EQ(tuple(4, -4, -3, 1), point(4, -4, -3));
}

TEST(AppTest, VectorTest){
    EXPECT_EQ(tuple(4, -4, -3, 0), vector(4, -4, -3));
}

TEST(AppTest, AddingTuplesTest){
    EXPECT_EQ(tuple(1, 1, 6, 1), tuple(3, -2, 5, 1) + tuple(-2, 3 ,1, 0));
}

TEST(AppTest, SubtractingPointPointTest){
    EXPECT_EQ(vector(-2, -4, -6), point(3, 2, 1) - point(5, 6, 7));
}

TEST(AppTest, SubtracingPointVectorTest){
    EXPECT_EQ(point(-2, -4, -6), point(3, 2, 1) - vector(5, 6, 7));
}

TEST(AppTest, SubtractingVectorVectorTest){
    EXPECT_EQ(vector(-2, -4, -6), vector(3, 2, 1) - vector(5, 6, 7));
}

TEST(AppTest, SubtracingZeroVectorTest){
    EXPECT_EQ(vector(-1, 2, -3), vector(0, 0, 0) - vector(1, -2, 3));
}

TEST(AppTest, NegateTupleTest){
    EXPECT_EQ(tuple(-1, 2, -3, 4), -tuple(1, -2, 3, -4));
}

TEST(AppTest, MultiplyTupleScalarTest){
    EXPECT_EQ(tuple(3.5, -7, 10.5, -14), tuple(1, -2, 3, -4) * 3.5);
}

TEST(AppTest, MultiplyTupleFractionTest){
    EXPECT_EQ(tuple(0.5, -1, 1.5, -2), tuple(1, -2, 3, -4) * 0.5);
}

TEST(AppTest, DivideTupleScalar){
    EXPECT_EQ(tuple(0.5, -1, 1.5, -2), tuple(1, -2, 3, -4) / 2);
}

TEST(AppTest, VectorMagnitudeTest){
    EXPECT_EQ(1, magnitude(vector(1, 0, 0)));
    EXPECT_EQ(1, magnitude(vector(0, 1, 0)));
    EXPECT_EQ(1, magnitude(vector(0, 0, 1)));

    //float comparison can be done with cmp_f function with EXPECT_EQ or EXPECT_FLOAT_EQ
    //EXPECT_FLOAT_EQ(sqrt(14), magnitude(vector(1, 2, 3)));
    EXPECT_TRUE(cmp_f(sqrt(14), magnitude(vector(1, 2, 3))));
    EXPECT_TRUE(cmp_f(sqrt(14), magnitude(vector(-1, -2, -3))));
}

//expression first, expected result after from here.

TEST(AppTest, NormalizeVectorTest){
    EXPECT_EQ(normalize(vector(4, 0, 0)), vector(1, 0, 0));
    EXPECT_EQ(normalize(vector(1, 2, 3)), vector(0.26726, 0.53452, 0.80178));
    EXPECT_FLOAT_EQ(magnitude(normalize(vector(1, 2, 3))), 1);
}

TEST(AppTest, DotProductTest){
    tuple a = vector(1, 2, 3);
    tuple b = vector(2, 3, 4);
    EXPECT_FLOAT_EQ(dot(a, b), 20);
}

TEST(AppTest, CrossProductTest){
    tuple a = vector(1, 2, 3);
    tuple b = vector(2, 3, 4);
    EXPECT_EQ(cross(a, b), vector(-1, 2, -1));
    EXPECT_EQ(cross(b, a), vector(1, -2, 1));
}

TEST(AppTest, ColorTest){
    EXPECT_EQ(Color(1.6, 0.7, 1.0), Color(0.9, 0.6, 0.75) + Color(0.7, 0.1, 0.25));
    EXPECT_EQ(Color(0.2, 0.5, 0.5), Color(0.9, 0.6, 0.75) - Color(0.7, 0.1, 0.25));
    EXPECT_EQ(Color(0.4, 0.6, 0.8), Color(0.2, 0.3, 0.4) * 2);
    EXPECT_EQ(Color(0.9, 0.2, 0.04), Color(1, 0.2, 0.4) * Color(0.9, 1, 0.1));
}

TEST(AppTest, CanvasTest){
    Color red = Color(1, 0, 0);
    Canvas c = Canvas(10, 20);
    EXPECT_EQ(c.width, 10);
    EXPECT_EQ(c.height, 20);
    for (int i = 0; i < c.height; ++i){
        for (int j = 0; j < c.width; ++j){
            EXPECT_EQ(c.canvas[i][j], Color(0, 0, 0));
        }
    }
    write_pixel(c, 2, 3, red);
    EXPECT_EQ(pixel_at(c, 2, 3), red);
}

TEST(AppTest, MatrixTest){
    Matrix mat = Matrix(4);
    mat.m = {{1,     2,     3,     4},
             {5.5 ,  6.5 ,  7.5 ,  8.5},
             {9 ,    10 ,   11 ,   12},
             {13.5 , 14.5 , 15.5 , 16.5}};
    EXPECT_EQ(mat.m[0][0], 1);
    EXPECT_EQ(mat.m[0][3], 4);
    EXPECT_EQ(mat.m[1][0], 5.5);
    EXPECT_EQ(mat.m[1][2], 7.5);
    EXPECT_EQ(mat.m[2][2], 11);
    EXPECT_EQ(mat.m[3][0], 13.5);
    EXPECT_EQ(mat.m[3][2], 15.5);

    Matrix mat2 = Matrix(2);
    mat2.m = {{-3,  5},
              { 1, -2}};
    EXPECT_EQ(mat2.m[0][0], -3);
    EXPECT_EQ(mat2.m[0][1], 5);
    EXPECT_EQ(mat2.m[1][0], 1);
    EXPECT_EQ(mat2.m[1][1], -2);

    Matrix mat3 = Matrix(3);
    mat3.m = {{-3,  5,  0},
              { 1, -2, -7},
              { 0,  1,  1}};
    EXPECT_EQ(mat3.m[0][0], -3);
    EXPECT_EQ(mat3.m[1][1], -2);
    EXPECT_EQ(mat3.m[2][2], 1);

    Matrix a1 = Matrix(4);
    Matrix b1 = Matrix(4);
    a1.m = {{1, 2, 3, 4},
           {5, 6, 7, 8},
           {9, 8, 7, 6},
           {5, 4, 3, 2}};
    b1.m = {{1 , 2 , 3 , 4},
            {5 , 6 , 7 , 8},
            {9 , 8 , 7 , 6},
            {5 , 4 , 3 , 2}};
    EXPECT_EQ(a1, b1);

    Matrix a2 = Matrix(4);
    Matrix b2 = Matrix(4);
    a2.m = {{ 1 , 2 , 3 , 4},
            { 5 , 6 , 7 , 8},
            { 9 , 8 , 7 , 6},
            { 5 , 4 , 3 , 2}};
    b2.m = {{ 2 , 3 , 4 , 5},
            { 6 , 7 , 8 , 9},
            { 8 , 7 , 6 , 5},
            { 4 , 3 , 2 , 1}};
    EXPECT_NE(a2, b2);
}

TEST(AppTest, MatrixMatrixMultiplyTest){
    Matrix a1  = Matrix(4);
    Matrix b1  = Matrix(4);
    Matrix res = Matrix(4);
    a1.m = {{1 , 2 , 3 , 4},
            {5 , 6 , 7 , 8},
            {9 , 8 , 7 , 6},
            {5 , 4 , 3 , 2}};
    b1.m = {{-2 , 1 , 2 ,  3},
            { 3 , 2 , 1 , -1},
            { 4 , 3 , 6 ,  5},
            { 1 , 2 , 7 ,  8}};
    res.m = {{20, 22 , 50  , 48 },
             {44, 54 , 114 , 108},
             {40, 58 , 110 , 102},
             {16, 26 , 46  , 42}};
    EXPECT_EQ(a1 * b1, res);
}

TEST(AppTest, MatrixTupleMultiplyTest){
    Matrix a1  = Matrix(4);
    tuple  b1  = tuple(1, 2, 3, 1);
    tuple  res = tuple(18, 24, 33, 1);
    a1.m = {{1 , 2 , 3 , 4},
            {2 , 4 , 4 , 2},
            {8 , 6 , 4 , 1},
            {0 , 0 , 0 , 1}};
    EXPECT_EQ(a1 * b1, res);
}

TEST(AppTest, MatrixIdentityMultiplyTest){
    Matrix a1  = Matrix(4);
    Matrix identity = Matrix::get_identity();
    a1.m = {{0 , 1 , 2  , 4   },
            {1 , 2 , 4  , 8   },
            {2 , 4 , 8  , 16  },
            {4 , 8 , 16 , 32 }};
    EXPECT_EQ(a1 * identity, a1);

    tuple t1 = tuple(1, 2, 3, 4);
    EXPECT_EQ(identity * t1, t1);
}

TEST(AppTest, MatrixTransposeTest){
    Matrix a1 = Matrix(4);
    Matrix a2 = Matrix(4);
    a1.m = {{0 , 9 , 3 , 0 },
            {9 , 8 , 0 , 8 },
            {1 , 8 , 5 , 3 },
            {0 , 0 , 5 , 8 }};
    a2.m = {{0 , 9 , 1 , 0 },
            {9 , 8 , 8 , 0 },
            {3 , 0 , 5 , 5 },
            {0 , 8 , 3 , 8 }};
    EXPECT_EQ(a2, transpose(a1));
    EXPECT_EQ(Matrix::get_identity(), transpose(Matrix::get_identity()));
}

TEST(AppTest, MatrixDeterminant2Test){
    Matrix a1 = Matrix(2);
    a1.m = {{ 1, 5},
            {-3, 2}};
    EXPECT_EQ(determinant(a1), 17);
}

TEST(AppTest, MatrixSubMatrixTest){
    Matrix a1 = Matrix(3);
    Matrix a2 = Matrix(2);
    a1.m = {{ 1, 5, 0},
            {-3, 2, 7},
            { 0, 6, -3}};
    a2.m = {{-3, 2},
            { 0, 6}};
    EXPECT_EQ(submatrix(a1, 0, 2), a2);

    Matrix b1 = Matrix(4);
    Matrix b2 = Matrix(3);
    b1.m = {{-6,  1 ,  1 , 6 },
            {-8 , 5 ,  8 , 6 },
            {-1 , 0 ,  8 , 2 },
            {-7 , 1 , -1 , 1 }};
    b2.m = {{ -6, 1, 6},
            {-8, 8,  6},
            {-7, -1, 1}};
    EXPECT_EQ(submatrix(b1, 2, 1), b2);
}

TEST(AppTest, MatrixMinorTest){
    Matrix a1 = Matrix(3);
    Matrix a2 = Matrix(2);
    a1.m = {{3,  5,  0},
            {2, -1, -7},
            {6, -1,  5}};
    a2 = submatrix(a1, 1, 0);
    float det = determinant(a2);
    EXPECT_EQ(mat_minor(a1, 1, 0), det);
}

TEST(AppTest, MatrixCofactorTest){
    Matrix a1 = Matrix(3);
    a1.m = {{3,  5,  0},
            {2, -1, -7},
            {6, -1,  5}};
    EXPECT_EQ(mat_minor(a1, 0, 0), -12);
    EXPECT_EQ(cofactor(a1, 0, 0), -12);
    EXPECT_EQ(mat_minor(a1, 1, 0), 25);
    EXPECT_EQ(cofactor(a1, 1, 0), -25);
}

TEST(AppTest, MatrixDeterminant3and4Test){
    Matrix a1 = Matrix(3);
    Matrix a2 = Matrix(4);
    a1.m = {{ 1, 2, 6},
            { -5, 8, -4},
            { 2, 6, 4}};
    a2.m = {{-2, -8 , 3 , 5 },
            {-3 , 1 , 7 , 3 },
            { 1 , 2 , -9 , 6 },
            {-6 , 7 , 7 , -9 }};
    EXPECT_EQ(cofactor(a1, 0, 0), 56);
    EXPECT_EQ(cofactor(a1, 0, 1), 12);
    EXPECT_EQ(cofactor(a1, 0, 2), -46);
    EXPECT_EQ(determinant(a1), -196);

    EXPECT_EQ(cofactor(a2, 0, 0), 690);
    EXPECT_EQ(cofactor(a2, 0, 1), 447);
    EXPECT_EQ(cofactor(a2, 0, 2), 210);
    EXPECT_EQ(cofactor(a2, 0, 3), 51);
    EXPECT_EQ(determinant(a2), -4071);
}

TEST(AppTest, MatrixIsInvertibleTest){
    Matrix a1 = Matrix(4);
    Matrix a2 = Matrix(4);
    a1.m = {{ 6,  4 , 4 ,  4 },
            { 5 , 5 , 7 ,  6 },
            { 4 ,-9 , 3 , -7 },
            { 9 , 1 , 7 , -6 }};
    a2.m = {{-4,  2 ,-2 , -3 },
            { 9 , 6 , 2 ,  6 },
            { 0 ,-5 , 1 , -5 },
            { 0 , 0 , 0 ,  0 }};
    EXPECT_EQ(determinant(a1), -2120);
    EXPECT_TRUE(is_invertible(a1));
    EXPECT_EQ(determinant(a2), 0);
    EXPECT_FALSE(is_invertible(a2));
}

TEST(AppTest, MatrixInverionTest) {
    Matrix a1 = Matrix(4);
    Matrix b = Matrix(4);
    Matrix inv = Matrix(4);
    a1.m = {{-5, 2,  6,  -8},
            {1,  -5, 1,  8},
            {7,  7,  -6, -7},
            {1,  -3, 7,  4}};
    inv.m = {{0.21805,  0.45113,  0.24060,  -0.04511},
             {-0.80827, -1.45677, -0.44361, 0.52068},
             {-0.07895, -0.22368, -0.05263, 0.19737},
             {-0.52256, -0.81391, -0.30075, 0.30639}};
    b = inverse(a1);
    EXPECT_EQ(determinant(a1), 532);
    EXPECT_EQ(cofactor(a1, 2, 3), -160);
    EXPECT_EQ(cofactor(a1, 3, 2), 105);
    EXPECT_FLOAT_EQ(b.m[3][2], -160 / 532.0);
    EXPECT_FLOAT_EQ(b.m[2][3], 105 / 532.0);
    EXPECT_EQ(b, inv);

    Matrix a2 = Matrix(4);
    Matrix inv2 = Matrix(4);
    Matrix a3 = Matrix(4);
    Matrix inv3 = Matrix(4);
    a2.m = {{8,  -5, 9,  2},
            {7,  5,  6,  1},
            {-6, 0,  9,  6},
            {-3, 0,  -9, -4}};
    a3.m = {{9,  3,  0,  9},
            {-5, -2, -6, -3},
            {-4, 9,  6,  4},
            {-7, 6,  6,  2}};
    inv2.m = {{-0.15385, -0.15385, -0.28205, -0.53846},
              {-0.07692, 0.12308,  0.02564,  0.03077},
              {0.35897,  0.35897,  0.43590,  0.92308},
              {-0.69231, -0.69231, -0.76923, -1.92308}};
    inv3.m = {{-0.04074, -0.07778, 0.14444,  -0.22222},
              {-0.07778, 0.03333,  0.36667,  -0.33333},
              {-0.02901, -0.14630, -0.10926, 0.12963},
              {0.17778,  0.06667,  -0.26667, 0.33333}};
    EXPECT_EQ(inverse(a2), inv2);
    EXPECT_EQ(inverse(a3), inv3);

    Matrix a4 = Matrix(4);
    Matrix b4 = Matrix(4);
    Matrix c4 = Matrix(4);
    a4.m = {{3,  -9, 7,  3},
            {3,  -8, 2,  -9},
            {-4, 4,  4,  1},
            {-6, 5,  -1, 1}};
    b4.m = {{ 8 , 2 , 2 , 2 },
            { 3 , -1 , 7 , 0 },
            { 7 , 0 , 5 , 4 },
            { 6 , -2 , 0 , 5 }};
    c4 = a4 * b4;
    EXPECT_EQ(c4 * inverse(b4), a4);
}

TEST(AppTest, TranlsationMatrixTest) {
    Matrix transform = translation(5, -3, 2);
    tuple p = point(-3, 4, 5);
    EXPECT_EQ(transform * p, point(2, 1, 7));

    transform = translation(5, -3, 2);
    Matrix inv = inverse(transform);
    p = point(-3, 4, 5);
    EXPECT_EQ(inv * p, point(-8, 7, 3));

    transform = translation(5, -3, 2);
    tuple v = vector(-3, 4, 5);
    EXPECT_EQ(transform * v, v);
}

TEST(AppTest, ScalingMatrixTest) {
    Matrix transform = scaling(2, 3, 4);
    tuple p = point(-4, 6, 8);
    EXPECT_EQ(transform * p, point(-8, 18, 32));

    transform = scaling(2, 3, 4);
    tuple v = vector(-4, 6, 8);
    EXPECT_EQ(transform * v, vector(-8, 18, 32));

    transform = scaling(2, 3, 4);
    Matrix inv = inverse(transform);
    v = vector(-4, 6, 8);
    EXPECT_EQ(inv * v, vector(-2, 2, 2));

    transform = scaling(-1, 1, 1);
    p = point(2, 3, 4);
    EXPECT_EQ(transform * p, point(-2, 3, 4));
}

TEST(AppTest, RotationXMatrixTest) {
    tuple p = point(0, 1, 0);
    Matrix half_quarter = rotation_x(PI/ 4);
    Matrix full_quarter = rotation_x(PI/ 2);
    EXPECT_EQ(half_quarter * p, point(0, sqrt(2)/2, std::sqrt(2)/2));
    EXPECT_EQ(full_quarter * p, point(0, 0, 1));

    Matrix inv = inverse(half_quarter);
    EXPECT_EQ(inv * p, point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST(AppTest, RotationYMatrixTest) {
    tuple p = point(0, 0, 1);
    Matrix half_quarter = rotation_y(PI/ 4);
    Matrix full_quarter = rotation_y(PI/ 2);
    EXPECT_EQ(half_quarter * p, point(sqrt(2)/2, 0, sqrt(2)/2));
    EXPECT_EQ(full_quarter * p, point(1, 0, 0));
}

TEST(AppTest, RotationZMatrixTest) {
    tuple p = point(0, 1, 0);
    Matrix half_quarter = rotation_z(PI/ 4);
    Matrix full_quarter = rotation_z(PI/ 2);
    EXPECT_EQ(half_quarter * p, point(-sqrt(2)/2, sqrt(2)/2, 0));
    EXPECT_EQ(full_quarter * p, point(-1, 0, 0));
}

TEST(AppTest, ShearingMatrixTest) {
    tuple p = point(2, 3, 4);
    Matrix transform = shearing(1, 0, 0, 0, 0, 0);
    EXPECT_EQ(transform * p, point(5, 3, 4));

    transform = shearing(0, 1, 0, 0, 0, 0);
    EXPECT_EQ(transform * p, point(6, 3, 4));
    transform = shearing(0, 0, 1, 0, 0, 0);
    EXPECT_EQ(transform * p, point(2, 5, 4));
    transform = shearing(0, 0, 0, 1, 0, 0);
    EXPECT_EQ(transform * p, point(2, 7, 4));
    transform = shearing(0, 0, 0, 0, 1, 0);
    EXPECT_EQ(transform * p, point(2, 3, 6));
    transform = shearing(0, 0, 0, 0, 0, 1);
    EXPECT_EQ(transform * p, point(2, 3, 7));
}

TEST(AppTest, OrderOfTransormationTest) {
    tuple p1 = point(1, 0, 1);
    Matrix A = rotation_x(PI / 2);
    Matrix B = scaling(5, 5, 5);
    Matrix C = translation(10, 5, 7);

    tuple p2 = A * p1;
    EXPECT_EQ(p2, point(1, -1, 0));
    tuple p3 = B * p2;
    EXPECT_EQ(p3, point(5, -5, 0));
    tuple p4 = C * p3;
    EXPECT_EQ(p4, point(15, 0, 7));

    Matrix T = C * B * A;
    EXPECT_EQ(T * p1, point(15, 0, 7));
}

TEST(RayCasting, RayQueryTest){
    tuple origin = point(1, 2, 3);
    tuple direction = vector(4, 5, 6);
    Ray r = Ray(origin, direction);
    EXPECT_EQ(r.origin, origin);
    EXPECT_EQ(r.direction, direction);

    r = Ray(point(2, 3, 4), vector(1, 0, 0));
    EXPECT_EQ(r.position(0), point(2, 3, 4));
    EXPECT_EQ(r.position(1), point(3, 3, 4));
    EXPECT_EQ(r.position(-1), point(1, 3, 4));
    EXPECT_EQ(r.position(2.5), point(4.5, 3, 4));
}

TEST(RayCasting, SphereIntersectTest){
    Ray r(point(0, 0, -5), vector(0, 0, 1));
    Sphere s;
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_FLOAT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 6.0f);
}

TEST(RayCasting, SphereIntersectTangentTest) {
    Ray r(point(0, 1, -5), vector(0, 0, 1));
    Sphere s;
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_FLOAT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 5.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 5.0f);
}

TEST(RayCasting, SphereIntersectMissTest) {
    Ray r(point(0, 2, -5), vector(0, 0, 1));
    Sphere s;
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_FLOAT_EQ(xs.size(), 0);
}


TEST(RayCasting, SphereIntersectInsideTest) {
    Ray r(point(0, 0, 0), vector(0, 0, 1));
    Sphere s;
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_FLOAT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -1.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 1.0f);
}

TEST(RayCasting, SphereIntersectBehindTest) {
    Ray r(point(0, 0, 5), vector(0, 0, 1));
    Sphere s;
    std::vector<Intersection> xs = s.intersect(r);
    EXPECT_FLOAT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -6.0f);
    EXPECT_FLOAT_EQ(xs[1].t, -4.0f);
}

TEST(RayCasting, IntersectTest) {
    std::shared_ptr<Shape> s = std::make_shared<Sphere>();
    Intersection i(3.5, s.get());
    EXPECT_FLOAT_EQ(i.t, 3.5);
    EXPECT_EQ(i.s, s.get());
}

TEST(RayCasting, IntersectionsTest) {
    Sphere s = Sphere();
    Intersection i1(1, &s);
    Intersection i2(2, &s);
    std::vector<Intersection> xs = intersections(i1, i2);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[1].t, 2);
}

TEST(RayCasting, IntersectionsObjectTest) {
    Ray r(point(0, 0, -5), vector(0, 0, 1));
    auto s = Sphere();
    auto xs = s.intersect(r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].s, &s);
    EXPECT_EQ(xs[1].s, &s);
}

TEST(RayCasting, IntersectionAllPositive) {
    auto s = Sphere();
    Intersection i1(1, &s);
    Intersection i2(2, &s);
    auto xs = intersections(i2, i1);
    Intersection i = hit(xs);
    EXPECT_FALSE(i.none);
    EXPECT_EQ(i, i1);
}

TEST(RayCasting, IntersectionSomeNegative){
    Sphere s = Sphere();
    Intersection i1(-1, &s);
    Intersection i2(1, &s);
    auto xs = intersections(i2, i1);
    Intersection i = hit(xs);
    EXPECT_FALSE(i.none);
    EXPECT_EQ(i, i2);
}

TEST(RayCasting, IntersectionAllNegative){
    Sphere s = Sphere();
    Intersection i1(-2, &s);
    Intersection i2(-1, &s);
    auto xs = intersections(i2, i1);
    Intersection i = hit(xs);
    EXPECT_TRUE(i.none);
}

TEST(RayCasting, IntersectionResultIsNonegative){
    Sphere s = Sphere();
    Intersection i1(5, &s);
    Intersection i2(7, &s);
    Intersection i3(-3, &s);
    Intersection i4(2, &s);
    auto xs = intersections(i1, i2, i3, i4);
    Intersection i = hit(xs);
    EXPECT_FALSE(i.none);
    EXPECT_EQ(i, i4);
}

TEST(RayCasting, RayTranslateTest) {
    Ray r = Ray(point(1, 2, 3), vector(0, 1, 0));
    Matrix m = translation(3, 4, 5);
    Ray r2 = r.transform(m);
    EXPECT_EQ(r2.origin, point(4, 6, 8));
    EXPECT_EQ(r2.direction, vector(0, 1, 0));
}

TEST(RayCasting, RayScaleTest) {
    Ray r = Ray(point(1, 2, 3), vector(0, 1, 0));
    Matrix m = scaling(2, 3, 4);
    Ray r2 = r.transform(m);
    EXPECT_EQ(r2.origin, point(2, 6, 12));
    EXPECT_EQ(r2.direction, vector(0, 3, 0));
}

TEST(RayCasting, TestShapeTransformTest) {
    TestShape s = TestShape();
    EXPECT_EQ(s.transform, Matrix::get_identity());

    Matrix t = translation(2.0f, 3.0f, 4.0f);
    s.set_transform(t);
    EXPECT_EQ(s.transform, t);
}

TEST(RayCasting, TestShapeRayIntersectTest) {
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    TestShape s = TestShape();
    s.set_transform(scaling(2, 2, 2));
    auto xs = s.intersect(r);
    EXPECT_EQ(s.saved_ray.origin, point(0, 0, -2.5)); 
    EXPECT_EQ(s.saved_ray.direction, vector(0, 0, 0.5)); 
    
}

TEST(LightShading, SphereNormalXaxisTest) {
    auto s = Sphere();
    tuple n = s.normal_at(point(1, 0, 0));
    EXPECT_EQ(n, vector(1, 0, 0));
}

TEST(LightShading, SphereNormalYaxisTest) {
    auto s = Sphere();
    tuple n = s.normal_at(point(0, 1, 0));
    EXPECT_EQ(n, vector(0, 1, 0));
}

TEST(LightShading, SphereNormalZaxisTest) {
    auto s = Sphere();
    tuple n = s.normal_at(point(0, 0, 1));
    EXPECT_EQ(n, vector(0, 0, 1));
}

TEST(LightShading, SphereNormalNonAxialTest) {
    auto s = Sphere();
    tuple n = s.normal_at(point(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));
    EXPECT_EQ(n, vector(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));
}

TEST(LightShading, SphereNormalNormalizedTest) {
    auto s = Sphere();
    tuple n = s.normal_at(point(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));
    EXPECT_EQ(n, normalize(n));
}

TEST(LightShading, TestShapeNormalTranslated) {
    TestShape s = TestShape();
    s.set_transform(translation(0, 1, 0));
    tuple n = s.normal_at(point(0, 1.70711, -0.70711));
    EXPECT_EQ(n, vector(0, 0.70711, -0.70711));
}

TEST(LightShading, TestShapeNormalTransformed) {
    TestShape s = TestShape();
    Matrix m = scaling(1, 0.5, 1) * rotation_z(PI / 5);
    s.set_transform(m);
    tuple n = s.normal_at(point(0, sqrt(2) / 2, -sqrt(2) / 2));
    EXPECT_EQ(n, vector(0, 0.97014, -0.24254));
}

TEST(LightShading, ReflectVector45degTest) {
    tuple v = vector(1, -1, 0);
    tuple n = vector(0, 1, 0);
    tuple r = reflect(v, n);
    EXPECT_EQ(r, vector(1, 1, 0));
}

TEST(LightShading, ReflectVectorSlantedSurfTest) {
    tuple v = vector(0, -1, 0);
    tuple n = vector(sqrt(2) / 2, sqrt(2)/2, 0);
    tuple r = reflect(v, n);
    EXPECT_EQ(r, vector(1, 0, 0));
}

TEST(LightShading, PointLightTest) {
    Color intensity = Color(1, 1, 1);
    tuple position = point(0, 0, 0);
    Point_light light = Point_light(position, intensity);
    EXPECT_EQ(light.position, position);
    EXPECT_EQ(light.intensity, intensity);
}

TEST(LightShading, DefaultMaterialTest) {
    Material m = Material();
    EXPECT_EQ(m.color, Color(1, 1, 1));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200.0);
}

TEST(LightShading, SphereMaterialTest) {
    TestShape s = TestShape();
    Material m = s.material;
    EXPECT_EQ(m, Material());

    m.ambient = 1.0f;
    s.material = m;
    EXPECT_EQ(s.material, m);
}

TEST(LightShading, MaterialsLightingTest) {
    Material m = Material();
    tuple position = point(0, 0, 0);

    Sphere s = Sphere();
    tuple eyev = vector(0, 0, -1);
    tuple normalv = vector(0, 0, -1);
    Point_light light = Point_light(point(0, 0, -10), Color(1, 1, 1));
    Color result = lighting(m, &s, light, position, eyev, normalv, false);
    EXPECT_EQ(result, Color(1.9, 1.9, 1.9));

    eyev = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
    normalv = vector(0, 0, -1);
    light = Point_light(point(0, 0, -10), Color(1, 1, 1));
    result = lighting(m, &s, light, position, eyev, normalv, false);
    EXPECT_EQ(result, Color(1.0, 1.0, 1.0));

    eyev = vector(0, 0, -1);
    normalv = vector(0, 0, -1);
    light = Point_light(point(0, 10, -10), Color(1, 1, 1));
    result = lighting(m, &s, light, position, eyev, normalv, false);
    EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));

    eyev = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
    normalv = vector(0, 0, -1);
    light = Point_light(point(0, 10, -10), Color(1, 1, 1));
    result = lighting(m, &s, light, position, eyev, normalv, false);
    EXPECT_EQ(result, Color(1.63639, 1.63639, 1.63639));

    eyev = vector(0, 0, -1);
    normalv = vector(0, 0, -1);
    light = Point_light(point(0, 0, 10), Color(1, 1, 1));
    result = lighting(m, &s, light, position, eyev, normalv, false);
    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST(WorldScene, DefaultWorldTest) {
    World w1 = World();
    EXPECT_EQ(w1.shapes.size(), 0);
    EXPECT_FALSE(w1.light_source.has_value());

    World w2 = World::get_default_world();
    EXPECT_EQ(w2.shapes.size(), 2);
    EXPECT_TRUE(w2.light_source.has_value());
}

TEST(WorldScene, DefaultWorldIntersectionTest) {
    World w = World::get_default_world();
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    auto xs = w.intersect_world(r);
    EXPECT_EQ(xs.size(), 4);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 4.5);
    EXPECT_FLOAT_EQ(xs[2].t, 5.5);
    EXPECT_FLOAT_EQ(xs[3].t, 6);
}

TEST(WorldScene, PrepareComputationsTest) {
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(4, &s);
    auto comps = prepare_computations(i, r);
    EXPECT_EQ(comps.s, &s);
    EXPECT_EQ(comps.p, point(0, 0, -1));
    EXPECT_EQ(comps.eyev, vector(0, 0, -1));
    EXPECT_EQ(comps.normalv, vector(0, 0, -1));
}

TEST(WorldScene, HitInsideTest) {
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    Intersection i = Intersection(4, &s);
    Computation comps = prepare_computations(i, r);
    EXPECT_FALSE(comps.inside);

    r = Ray(point(0, 0, 0), vector(0, 0, 1));
    s = Sphere();
    i = Intersection(1, &s);
    comps = prepare_computations(i, r);
    EXPECT_EQ(comps.p, point(0, 0, 1));
    EXPECT_EQ(comps.eyev, vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    EXPECT_EQ(comps.normalv, vector(0, 0, -1));
}

TEST(WorldScene, ShadingIntersectionTest){
    World w = World::get_default_world();
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    std::shared_ptr<Shape> s = w.shapes[0];
    Intersection i = Intersection(4, s.get());
    Computation comps = prepare_computations(i, r);
    Color c = shade_hit(w, comps);
    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldScene, ShadingIntersectionFromInsideTest){
    World w = World::get_default_world();
    w.light_source = Point_light(point(0, 0.25, 0), Color(1, 1, 1));
    Ray r = Ray(point(0, 0, 0), vector(0, 0, 1));
    std::shared_ptr<Shape> s = w.shapes[1];
    Intersection i = Intersection(0.5, s.get());
    Computation comps = prepare_computations(i, r);
    Color c = shade_hit(w, comps);
    EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldScene, ColorAtTest){
    World w = World::get_default_world();
    Ray r = Ray(point(0, 0, -5), vector(0, 1, 0));
    Color c = color_at(w, r);
    EXPECT_EQ(c, Color(0, 0, 0));

    w = World::get_default_world();
    r = Ray(point(0, 0, -5), vector(0, 0, 1));
    c = color_at(w, r);
    EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));

    w = World::get_default_world();
    std::shared_ptr<Shape> outer = w.shapes[0];
    outer->material.ambient = 1;
    std::shared_ptr<Shape> inner = w.shapes[1];
    inner->material.ambient = 1;
    r = Ray(point(0, 0, 0.75), vector(0, 0, -1));
    c = color_at(w, r);
    EXPECT_EQ(c, inner->material.color);
}

TEST(WorldScene, DefaultOrientationTest){
    tuple from = point(0, 0, 0);
    tuple to = point(0, 0, -1);
    tuple up = vector(0, 1, 0);
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, Matrix::get_identity());
}

TEST(WorldScene, PosZOrientationTest){
    tuple from = point(0, 0, 0);
    tuple to = point(0, 0, 1);
    tuple up = vector(0, 1, 0);
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, scaling(-1, 1, -1));
}

TEST(WorldScene, ViewTransformationMovesWorldTest){
    tuple from = point(0, 0, 8);
    tuple to = point(0, 0, 0);
    tuple up = vector(0, 1, 0);
    Matrix t = view_transform(from, to, up);
    EXPECT_EQ(t, translation(0, 0, -8));
}

TEST(WorldScene, ViewTransformationTest){
    tuple from = point(1, 3, 2);
    tuple to = point(4, -2, 8);
    tuple up = vector(1, 1, 0);
    Matrix t = view_transform(from, to, up);
    Matrix mat = Matrix(4);
    mat.m = {{-0.50709, 0.50709,  0.67612, -2.36643},
             { 0.76772, 0.60609,  0.12122, -2.82843},
             {-0.35857, 0.59761, -0.71714,  0.00000},
             { 0.00000, 0.00000,  0.00000,  1.00000}};
    EXPECT_EQ(t, mat);
}

TEST(WorldScene, ConstructingCameraTest){
    int hsize = 160, vsize = 120;
    float fov = PI / 2.0f;
    Camera cam = Camera(hsize, vsize, fov);
    EXPECT_EQ(cam.hsize, hsize);
    EXPECT_EQ(cam.vsize, vsize);
    EXPECT_FLOAT_EQ(cam.fov, fov);
}

TEST(WorldScene, CameraPixelSizeHorizontalCanvasTest){
    Camera cam = Camera(200, 125, PI/2.0f);
    EXPECT_TRUE(cmp_f(cam.pixel_size, 0.01f));
}

TEST(WorldScene, CameraPixelSizeVerticalCanvasTest){
    Camera cam = Camera(125, 200, PI/2.0f);
    EXPECT_TRUE(cmp_f(cam.pixel_size, 0.01f));
}

TEST(WorldScene, ConstructingRayThroughCenterTest){
    Camera cam = Camera(201, 101, PI/2.0f);
    Ray r = cam.ray_for_pixel(100, 50);
    EXPECT_EQ(r.origin, point(0, 0, 0));
    EXPECT_EQ(r.direction, vector(0, 0, -1));
}

TEST(WorldScene, ConstructingRayThroughCornerTest){
    Camera cam = Camera(201, 101, PI/2.0f);
    Ray r = cam.ray_for_pixel(0, 0);
    EXPECT_EQ(r.origin, point(0, 0, 0));
    EXPECT_EQ(r.direction, vector(0.66519, 0.33259, -0.66851));
}

TEST(WorldScene, ConstructingRayCameraTransformedTest){
    Camera cam = Camera(201, 101, PI/2.0f);
    cam.set_transform(rotation_y(PI/4.0f) * translation(0, -2, 5));
    Ray r = cam.ray_for_pixel(100, 50);
    EXPECT_EQ(r.origin, point(0, 2, -5));
    EXPECT_EQ(r.direction, vector(sqrt(2.0f) / 2.0f, 0, -sqrt(2.0f) / 2.0f));
}

TEST(WorldScene, RenderingWorldTest){
    World world = World::get_default_world();
    Camera cam = Camera(11, 11, PI/2.0f);
    tuple from = point(0, 0, -5);
    tuple to = point(0, 0, 0);
    tuple up = vector(0, 1, 0);
    cam.set_transform(view_transform(from, to, up));
    Canvas image = render(cam, world);
    EXPECT_EQ(pixel_at(image, 5, 5), Color(0.38066, 0.47583, 0.2855));
}

TEST(Shadows, NoShadowBetweenTest){
    World world = World::get_default_world();
    tuple p = point(0, 10, 0);
    EXPECT_FALSE(is_shadowed(world, p));
}

TEST(Shadows, NoShadowObjectBehindLightTest){
    World world = World::get_default_world();
    tuple p = point(10, -10, 10);
    EXPECT_TRUE(is_shadowed(world, p));
}

TEST(Shadows, NoShadowObjectBehindPointTest){
    World world = World::get_default_world();
    tuple p = point(-2, 2, -2);
    EXPECT_FALSE(is_shadowed(world, p));
}

TEST(Shadows, HitOffsetPointTest){
    Ray r = Ray(point(0, 0, -5), vector(0, 0, 1));
    Sphere s = Sphere();
    s.set_transform(translation(0, 0, 1));
    Intersection i = Intersection(5, &s);
    Computation comps = prepare_computations(i, r);
    EXPECT_LT(comps.over_point.z, -EPSILON/2.0f);
    EXPECT_GT(comps.p.z, comps.over_point.z);
}

TEST(Planes, PlaneNormalTest){
    Plane p = Plane();
    tuple n1 = p.local_normal_at(point(0, 0, 0));
    tuple n2 = p.local_normal_at(point(10, 0, -10));
    tuple n3 = p.local_normal_at(point(-5, 0, 150));
    EXPECT_EQ(n1, vector(0, 1, 0));
    EXPECT_EQ(n2, vector(0, 1, 0));
    EXPECT_EQ(n3, vector(0, 1, 0));
}

TEST(Planes, PlaneIntersectTest){
    Plane p = Plane();
    Ray r = Ray(point(0, 10, 0), vector(0, 0, 1));
    auto xs = p.local_intersect(r);
    EXPECT_EQ(xs.size(), 0);

    Plane p2 = Plane();
    Ray r2 = Ray(point(0, 0, 0), vector(0, 0, 1));
    auto xs2 = p2.local_intersect(r2);
    EXPECT_EQ(xs2.size(), 0);
}

TEST(Planes, PlaneAboveIntersectTest){
    Plane p = Plane();
    Ray r = Ray(point(0, 1, 0), vector(0, -1, 0));
    auto xs = p.local_intersect(r);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].s, &p);
}

TEST(Planes, PlaneBelowIntersectTest){
    Plane p = Plane();
    Ray r = Ray(point(0, -1, 0), vector(0, 1, 0));
    auto xs = p.local_intersect(r);
    EXPECT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].s, &p);
}

TEST(Patterns, TestPatternCreationTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    TestPattern pattern = TestPattern(white, black);
    EXPECT_EQ(pattern.a, white);
    EXPECT_EQ(pattern.b, black);
}

TEST(Patterns, StripeAtTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Stripe_pattern pattern = Stripe_pattern(white, black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0, 1, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0, 2, 0)) , white);
    
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 1)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 2)) , white);
    
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0.9, 0, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(1, 0, 0)) , black);
    EXPECT_EQ(pattern.pattern_at(point(-0.1, 0, 0)) , black);
    EXPECT_EQ(pattern.pattern_at(point(-1, 0, 0)) , black);
    EXPECT_EQ(pattern.pattern_at(point(-1.1, 0, 0)) , white);
}

TEST(Patterns, PatternLightingTest){
    Material m;
    Sphere s = Sphere();
    Stripe_pattern p = Stripe_pattern(Color(1, 1, 1), Color(0, 0, 0));
    m.pattern = &p;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    auto eyev = vector(0, 0, -1);
    auto normalv = vector(0, 0, -1);
    auto light = Point_light(point(0, 0, -10), Color(1, 1, 1));
    auto c1 = lighting(m, &s, light, point(0.9, 0, 0), eyev, normalv, false);
    auto c2 = lighting(m, &s, light, point(1.1, 0, 0), eyev, normalv, false);
    EXPECT_EQ(c1 , Color(1, 1, 1));
    EXPECT_EQ(c2 , Color(0, 0, 0));
}

TEST(Patterns, PatternObjectTransformationTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Sphere object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    Stripe_pattern pattern = Stripe_pattern(white, black);
    Color c = pattern_at_shape(&pattern, &object, point(1.5, 0, 0));
    EXPECT_EQ(c, white);
}

TEST(Patterns, PatternTransformationTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Sphere object = Sphere();
    Stripe_pattern pattern = Stripe_pattern(white, black);
    pattern.set_transform(scaling(2, 2, 2));
    Color c = pattern_at_shape(&pattern, &object, point(1.5, 0, 0));
    EXPECT_EQ(c, white);
}
TEST(Patterns, PatternAndObjectTransformationTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Sphere object = Sphere();
    object.set_transform(scaling(2, 2, 2));
    Stripe_pattern pattern = Stripe_pattern(white, black);
    pattern.set_transform(translation(0.5, 0, 0));
    Color c = pattern_at_shape(&pattern, &object, point(2.5, 0, 0));
    EXPECT_EQ(c, white);
}

TEST(Patterns, GradientPatternTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Gradient_pattern pattern = Gradient_pattern(white, black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)) , white);
    EXPECT_EQ(pattern.pattern_at(point(0.25, 0, 0)) , Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.pattern_at(point(0.5, 0, 0)) , Color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.pattern_at(point(0.75, 0, 0)) , Color(0.25, 0.25, 0.25));
}

TEST(Patterns, RingPatternTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);

    Ring_pattern pattern = Ring_pattern(white, black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_at(point(1, 0, 0)), black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 1)), black);
    EXPECT_EQ(pattern.pattern_at(point(0.708, 0, 0.708)), black);
}

TEST(Patterns, CheckerPatternTest){
    Color black = Color(0, 0, 0);
    Color white = Color(1, 1, 1);
    
    Checker_pattern pattern = Checker_pattern(white, black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)), white); 
    EXPECT_EQ(pattern.pattern_at(point(0.99, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_at(point(1.01, 0, 0)), black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_at(point(0, 0.99, 0)), white);
    EXPECT_EQ(pattern.pattern_at(point(0, 1.01, 0)), black);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0)), white);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 0.99)),  white);
    EXPECT_EQ(pattern.pattern_at(point(0, 0, 1.01)), black);
}