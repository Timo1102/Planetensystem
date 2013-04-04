#ifndef _RK_QUATERNION_HPP_
#define _RK_QUATERNION_HPP_

#include "datatypes.hpp"
#include "defines.hpp"
#include "vector.hpp"

namespace RK
{
    class RK_LIBRARY Quaternion
    {
        public:
            Quaternion();
            Quaternion(RKfloat x, RKfloat y, RKfloat z, RKfloat w);
            Quaternion(const Vector &axis, RKfloat angle);
            ~Quaternion();

            Quaternion operator*(const Quaternion &other) const;
            Quaternion &operator*=(const Quaternion &other);
            Quaternion conjugate() const;
            Quaternion normal() const;
            Quaternion &normalize();
            Vector apply(const Vector &vector) const;

            union
            {
                struct
                {
                    RKfloat x, y, z, w;
                };
                RKfloat data[4];
            };
    };

    Vector operator*(const Quaternion &quaternion, const Vector &vector);
    Vector operator*(const Vector &vector, const Quaternion &quaternion);
}

#endif