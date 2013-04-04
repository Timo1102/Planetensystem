#ifndef _RK_MATRIX_HPP_
#define _RK_MATRIX_HPP_

#include "datatypes.hpp"
#include "defines.hpp"
#include "quaternion.hpp"

namespace RK
{
    class Matrix
    {
        public:
            Matrix();
            Matrix(RKfloat m00, RKfloat m01, RKfloat m02, RKfloat m03, RKfloat m10, RKfloat m11, RKfloat m12, RKfloat m13, RKfloat m20, RKfloat m21, RKfloat m22, RKfloat m23, RKfloat m30, RKfloat m31, RKfloat m32, RKfloat m33);
            Matrix(const Quaternion &copy);
            Matrix(const Vector &copy);
            Matrix(const RKfloat &copy);
            ~Matrix();

            RKfloat determinant() const;
            static Matrix Perspective(RKfloat cnear, RKfloat cfar, RKfloat width, RKfloat height, RKfloat fov);
            static Matrix Orthogonal(RKfloat cnear, RKfloat cfar, RKfloat width, RKfloat height);
            Matrix operator*(const Matrix &matrix) const;
            Matrix &operator*=(const Matrix &matrix);
            Vector apply(const Vector &vector) const;

            union
            {
                RKfloat data[16];
                struct
                {
                    RKfloat m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
                };
            };
    };
}

#endif