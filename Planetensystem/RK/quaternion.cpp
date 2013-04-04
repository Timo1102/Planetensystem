#include "quaternion.hpp"

#include <cmath>

namespace RK
{
    Quaternion::Quaternion()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        this->w = 1.0f;
    }

    Quaternion::Quaternion(RKfloat x, RKfloat y, RKfloat z, RKfloat w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::Quaternion(const Vector &axis, RKfloat angle)
    {
        Vector vector = axis.normal() * sinf(angle * 0.5f);

        this->x = vector.x;
        this->y = vector.y;
        this->z = vector.z;
        this->w = cos(angle * 0.5f);
    }

    Quaternion::~Quaternion()
    {
    }

    Quaternion Quaternion::operator*(const Quaternion &other) const
    {
        Quaternion result(
            this->w * other.x + this->x * other.w + this->y * other.z + this->z * other.y,
            this->w * other.y + this->y * other.w + this->z * other.x + this->x * other.z,
            this->w * other.z + this->z * other.w + this->x * other.y + this->y * other.x,
            this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z
        );

        return result;
    }

    Quaternion &Quaternion::operator*=(const Quaternion &other)
    {
        *this = *this * other;

        return *this;
    }

    Quaternion Quaternion::conjugate() const
    {
        return Quaternion(-this->x, -this->y, -this->z, this->w);
    }

    Quaternion Quaternion::normal() const
    {
        RKfloat length = this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;

        length = sqrtf(length);

        return Quaternion(this->x / length, this->y / length, this->z / length, this->w / length);
    }

    Quaternion &Quaternion::normalize()
    {
        *this = this->normal();

        return *this;
    }

    Vector Quaternion::apply(const Vector &vector) const
    {
        Quaternion temporary(vector.x, vector.y, vector.z, 0.0f);

        temporary = temporary * this->conjugate();
        temporary = *this * temporary;

        return Vector(temporary.x, temporary.y, temporary.z);
    }

    Vector operator*(const Quaternion &quaternion, const Vector &vector)
    {
        return quaternion.apply(vector);
    }

    Vector operator*(const Vector &vector, const Quaternion &quaternion)
    {
        return quaternion.apply(vector);
    }
}