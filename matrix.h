#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include "rt.h"

struct Matrix {
    std::vector<std::vector<float>> m;
    int m_size = 0;
    Matrix(int size){
        m_size = size;
        m.resize(m_size, std::vector<float>(m_size));
    };

    Matrix operator*(const Matrix &other){
        Matrix result = Matrix(m_size);
        for (int row = 0; row < m_size; row++){
            for (int col = 0; col < m_size; col++){
               result.m[row][col] = m[row][0] * other.m[0][col] +
                                    m[row][1] * other.m[1][col] +
                                    m[row][2] * other.m[2][col] +
                                    m[row][3] * other.m[3][col];
            }
        }
        return result;
    };

    tuple operator*(const tuple &other){
        tuple result = tuple(0, 0, 0, 0);
        result.x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * other.w;
        result.y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * other.w;
        result.z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * other.w;
        result.w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * other.w;
        return result;
    };

    bool operator==(const Matrix &other) const {
        for (int i = 0; i < m_size; i++){
            for (int j = 0; j < m_size; j++){
                if (!cmp_f(m[i][j], other.m[i][j])) return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix &other) const {
        return !(*this == other);
    }

    void print(){
        for (int i = 0; i < m_size; ++i){
            for (int j = 0; j < m_size; ++j){
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }





    static Matrix get_identity(){
        Matrix mat = Matrix(4);
        mat.m = {{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
        return mat;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (auto i : mat.m) {
            for (auto j : i) {
                os << j << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

Matrix transpose(const Matrix &mat){
    Matrix result = Matrix(mat.m_size);
    for (int i = 0; i < mat.m_size; i++){
        for (int j = 0; j <mat.m_size; j++){
            result.m[j][i] = mat.m[i][j];
        }
    }
    return result;
}

float cofactor(const Matrix &mat, int row, int col);

float determinant(const Matrix &mat){
    if (mat.m_size == 2)
        return (mat.m[0][0]*mat.m[1][1] - mat.m[0][1]*mat.m[1][0]);
    else{
        float det = 0;
        for (int j = 0; j < mat.m_size; j++){
            det += mat.m[0][j] * cofactor(mat, 0, j);
        }
        return det;
    }


}

Matrix submatrix(const Matrix &mat, int row, int col){
    Matrix result = Matrix(mat.m_size-1);
    for (int i = 0; i < mat.m_size; i++){
        if (row == i) continue;
        int deltaRow = 0;
        if (i > row){
            deltaRow = -1;
        }
        for (int j = 0; j < mat.m_size; j++){
            if (col == j) continue;
            int deltaCol = 0;
            if (j > col){
                deltaCol= -1;
            }
            int subRow = i+deltaRow;
            int subCol = j+deltaCol;
            result.m[subRow][subCol] = mat.m[i][j];
        }
    }
    return result;
}

float mat_minor(const Matrix &mat, int row, int col){
    return determinant(submatrix(mat, row, col));
}

float cofactor(const Matrix &mat, int row, int col){
    return mat_minor(mat, row, col) * (((row + col) % 2 == 0 ? 1 : -1));
}

bool is_invertible(const Matrix &mat){
    return determinant(mat) != 0;
}

Matrix inverse(const Matrix &mat){
    if (!is_invertible(mat))
        throw std::runtime_error("Matrix is non invertible");
    Matrix mat2 = Matrix(mat.m_size);
    for (int i = 0; i < mat.m_size; ++i) {
        for (int j = 0; j < mat.m_size; ++j) {
            float c = cofactor(mat, i, j);
            //mat2.m[j][i] = my_round(c / determinant(mat), 5);
            mat2.m[j][i] = c / determinant(mat);
        }
    }
    return mat2;
}

Matrix translation(float x, float y, float z){
    Matrix transform = Matrix::get_identity();
    transform.m[0][3] = x;
    transform.m[1][3] = y;
    transform.m[2][3] = z;
    return transform;
}

Matrix scaling(float x, float y, float z){
    Matrix transform = Matrix::get_identity();
    transform.m[0][0] = x;
    transform.m[1][1] = y;
    transform.m[2][2] = z;
    return transform;
}

Matrix rotation_x(float r){
    Matrix rotationx = Matrix(4);
    rotationx.m[0][0] = 1;
    rotationx.m[1][1] = cos(r);
    rotationx.m[1][2] = -sin(r);
    rotationx.m[2][1] = sin(r);
    rotationx.m[2][2] = cos(r);
    rotationx.m[3][3] = 1;
    return rotationx;
}

Matrix rotation_y(float r){
    Matrix rotationy = Matrix(4);
    rotationy.m[0][0] = cos(r);
    rotationy.m[0][2] = sin(r);
    rotationy.m[1][1] = 1;
    rotationy.m[2][0] = -sin(r);
    rotationy.m[2][2] = cos(r);
    rotationy.m[3][3] = 1;
    return rotationy;
}

Matrix rotation_z(float r){
    Matrix rotationz = Matrix(4);
    rotationz.m[0][0] = cos(r);
    rotationz.m[0][1] = -sin(r);
    rotationz.m[1][0] = sin(r);
    rotationz.m[1][1] = cos(r);
    rotationz.m[2][2] = 1;
    rotationz.m[3][3] = 1;
    return rotationz;
}

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy){
    Matrix shear = Matrix::get_identity();
    shear.m[0][1] = xy;
    shear.m[0][2] = xz;
    shear.m[1][0] = yx;
    shear.m[1][2] = yz;
    shear.m[2][0] = zx;
    shear.m[2][1] = zy;
    return shear;
}