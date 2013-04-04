#ifndef _RK_VECTOR_HPP_
#define _RK_VECTOR_HPP_

#include "datatypes.hpp"
#include "defines.hpp"

namespace RK
{
    class Vector
    {
        public:
            Vector();
            Vector(RKfloat x, RKfloat y, RKfloat z);
            ~Vector();

            Vector operator+(const Vector &vector) const;
            Vector operator-(const Vector &vector) const;
            Vector &operator+=(const Vector &vector);
            Vector &operator-=(const Vector &vector);
            Vector operator/(const RKfloat &scalar) const;
            Vector operator*(const RKfloat &scalar) const;
            Vector &operator/=(const RKfloat &scalar);
            Vector &operator*=(const RKfloat &scalar);

            RKfloat length() const;
            Vector normal() const;
            Vector &normalize();
            Vector &zero();

            RKfloat x, y, z;
    };
}

#endif