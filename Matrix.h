#pragma once
#include "rt.h"
#include <vector>
#include <iostream>
#include <stdexcept>


struct Matrix {
    std::vector<std::vector<float>> m;
    int m_size = 0;
    Matrix(int size);

    Matrix operator*(const Matrix &other);

    tuple operator*(const tuple &other);

    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    static Matrix get_identity();

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};

Matrix transpose(const Matrix &mat);

float cofactor(const Matrix &mat, int row, int col);

float determinant(const Matrix &mat);

Matrix submatrix(const Matrix &mat, int row, int col);

float mat_minor(const Matrix &mat, int row, int col);
float cofactor(const Matrix &mat, int row, int col);
bool is_invertible(const Matrix &mat);


Matrix inverse(const Matrix &a);



Matrix translation(float x, float y, float z);

Matrix scaling(float x, float y, float z);

Matrix rotation_x(float r);

Matrix rotation_y(float r);

Matrix rotation_z(float r);

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

Matrix view_transform(const tuple& from, const tuple& to, const tuple& up);
