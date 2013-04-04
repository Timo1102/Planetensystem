#include "matrix.hpp"

#include <cmath>

#ifndef RK_PI_180
#define RK_PI_180 static_cast<RKfloat>(3.14159265358979323846f / 180.0f)
#endif

namespace RK
{
    Matrix::Matrix()
    {
        this->m00 = 1.0f;
        this->m01 = 0.0f;
        this->m02 = 0.0f;
        this->m03 = 0.0f;
        this->m10 = 0.0f;
        this->m11 = 1.0f;
        this->m12 = 0.0f;
        this->m13 = 0.0f;
        this->m20 = 0.0f;
        this->m21 = 0.0f;
        this->m22 = 1.0f;
        this->m23 = 0.0f;
        this->m30 = 0.0f;
        this->m31 = 0.0f;
        this->m32 = 0.0f;
        this->m33 = 1.0f;
    }

    Matrix::Matrix(RKfloat m00, RKfloat m01, RKfloat m02, RKfloat m03, RKfloat m10, RKfloat m11, RKfloat m12, RKfloat m13, RKfloat m20, RKfloat m21, RKfloat m22, RKfloat m23, RKfloat m30, RKfloat m31, RKfloat m32, RKfloat m33)
    {
        this->m00 = m00;
        this->m01 = m01;
        this->m02 = m02;
        this->m03 = m03;
        this->m10 = m10;
        this->m11 = m11;
        this->m12 = m12;
        this->m13 = m13;
        this->m20 = m20;
        this->m21 = m21;
        this->m22 = m22;
        this->m23 = m23;
        this->m30 = m30;
        this->m31 = m31;
        this->m32 = m32;
        this->m33 = m33;
    }

    Matrix::Matrix(const Quaternion &copy)
    {
        this->m00 = 1.0f - 2.0f * copy.y * copy.y - 2.0f * copy.z * copy.z;
        this->m01 = 2.0f * copy.x * copy.y - 2.0f * copy.z * copy.w;
        this->m02 = 2.0f * copy.x * copy.z + 2.0f * copy.y * copy.w;
        this->m10 = 2.0f * copy.x * copy.y + 2.0f * copy.z * copy.w;
        this->m11 = 1.0f - 2.0f * copy.x * copy.x - 2.0f * copy.z * copy.z;
        this->m12 = 2.0f * copy.y * copy.z - 2.0f * copy.x * copy.w;
        this->m20 = 2.0f * copy.x * copy.z - 2.0f * copy.y * copy.w;
        this->m21 = 2.0f * copy.y * copy.z + 2.0f * copy.x * copy.w;
        this->m22 = 1.0f - 2.0f * copy.x * copy.x - 2.0f * copy.y * copy.y;
        this->m03 = 0.0f;
        this->m13 = 0.0f;
        this->m23 = 0.0f;
        this->m30 = 0.0f;
        this->m31 = 0.0f;
        this->m32 = 0.0f;
        this->m33 = 1.0f;
    }

    Matrix::Matrix(const Vector &copy)
    {
        this->m00 = 1.0f;
        this->m01 = 0.0f;
        this->m02 = 0.0f;
        this->m03 = 0.0f;
        this->m10 = 0.0f;
        this->m11 = 1.0f;
        this->m12 = 0.0f;
        this->m13 = 0.0f;
        this->m20 = 0.0f;
        this->m21 = 0.0f;
        this->m22 = 1.0f;
        this->m23 = 0.0f;
        this->m30 = copy.x;
        this->m31 = copy.y;
        this->m32 = copy.z;
        this->m33 = 1.0f;
    }

    Matrix::Matrix(const RKfloat &copy)
    {
        this->m00 = copy;
        this->m01 = 0.0f;
        this->m02 = 0.0f;
        this->m03 = 0.0f;
        this->m10 = 0.0f;
        this->m11 = copy;
        this->m12 = 0.0f;
        this->m13 = 0.0f;
        this->m20 = 0.0f;
        this->m21 = 0.0f;
        this->m22 = copy;
        this->m23 = 0.0f;
        this->m30 = 0.0f;
        this->m31 = 0.0f;
        this->m32 = 0.0f;
        this->m33 = 1.0f;
    }

    Matrix::~Matrix()
    {
    }

    Matrix Matrix::Perspective(RKfloat cnear, RKfloat cfar, RKfloat width, RKfloat height, RKfloat fov)
    {
        return Matrix(
            (2.0f * cnear / (2.0f * cnear * tanf(fov * RK_PI_180 * 0.5f))) / (width / height), 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f * cnear / (2.0f * cnear * tanf(fov * RK_PI_180 * 0.5f)), 0.0f, 0.0f,
            0.0f, 0.0f, -(cfar + cnear) / (cfar - cnear), -1.0f,
            0.0f, 0.0f, -2.0f * (cfar * cnear) / (cfar - cnear), 0.0f
        );
    }

    Matrix Matrix::Orthogonal(RKfloat cnear, RKfloat cfar, RKfloat width, RKfloat height)
    {
        return Matrix(
            2.0f / width, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f / height, 0.0f, 0.0f,
            0.0f, 0.0f, -2.0f / (cfar - cnear), 0.0f,
            0.0f, 0.0f, -(cfar + cnear) / (cfar - cnear), 1.0f
        );
    }

    RKfloat Matrix::determinant() const
    {
        return (
            this->m00 * this->m11 * this->m22 * this->m33 +
            this->m10 * this->m21 * this->m32 * this->m03 +
            this->m20 * this->m31 * this->m02 * this->m13 +
            this->m30 * this->m01 * this->m12 * this->m23 -
            this->m03 * this->m12 * this->m21 * this->m30 -
            this->m13 * this->m22 * this->m31 * this->m00 -
            this->m23 * this->m32 * this->m01 * this->m10 -
            this->m33 * this->m02 * this->m11 * this->m20
        );
    }

    Matrix Matrix::operator*(const Matrix &matrix) const
    {
        return Matrix(
            this->m00 * matrix.m00 + this->m01 * matrix.m10 + this->m02 * matrix.m20 + this->m03 * matrix.m30,
            this->m00 * matrix.m01 + this->m01 * matrix.m11 + this->m02 * matrix.m21 + this->m03 * matrix.m31,
            this->m00 * matrix.m02 + this->m01 * matrix.m12 + this->m02 * matrix.m22 + this->m03 * matrix.m32,
            this->m00 * matrix.m03 + this->m01 * matrix.m13 + this->m02 * matrix.m23 + this->m03 * matrix.m33,
            this->m10 * matrix.m00 + this->m11 * matrix.m10 + this->m12 * matrix.m20 + this->m13 * matrix.m30,
            this->m10 * matrix.m01 + this->m11 * matrix.m11 + this->m12 * matrix.m21 + this->m13 * matrix.m31,
            this->m10 * matrix.m02 + this->m11 * matrix.m12 + this->m12 * matrix.m22 + this->m13 * matrix.m32,
            this->m10 * matrix.m03 + this->m11 * matrix.m13 + this->m12 * matrix.m23 + this->m13 * matrix.m33,
            this->m20 * matrix.m00 + this->m21 * matrix.m10 + this->m22 * matrix.m20 + this->m23 * matrix.m30,
            this->m20 * matrix.m01 + this->m21 * matrix.m11 + this->m22 * matrix.m21 + this->m23 * matrix.m31,
            this->m20 * matrix.m02 + this->m21 * matrix.m12 + this->m22 * matrix.m22 + this->m23 * matrix.m32,
            this->m20 * matrix.m03 + this->m21 * matrix.m13 + this->m22 * matrix.m23 + this->m23 * matrix.m33,
            this->m30 * matrix.m00 + this->m31 * matrix.m10 + this->m32 * matrix.m20 + this->m33 * matrix.m30,
            this->m30 * matrix.m01 + this->m31 * matrix.m11 + this->m32 * matrix.m21 + this->m33 * matrix.m31,
            this->m30 * matrix.m02 + this->m31 * matrix.m12 + this->m32 * matrix.m22 + this->m33 * matrix.m32,
            this->m30 * matrix.m03 + this->m31 * matrix.m13 + this->m32 * matrix.m23 + this->m33 * matrix.m33
        );
    }

    Matrix &Matrix::operator*=(const Matrix &matrix)
    {
        *this = *this * matrix;

        return *this;
    }

    Vector Matrix::apply(const Vector &vector) const
    {
        return Vector(
            this->m00 * vector.x + this->m01 * vector.y + this->m02 * vector.z,
            this->m10 * vector.x + this->m11 * vector.y + this->m12 * vector.z,
            this->m20 * vector.x + this->m21 * vector.y + this->m22 * vector.z
        );
    }
}