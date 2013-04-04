#include "vector.hpp"

#include <cmath>

namespace RK
{
    Vector::Vector()
    {
        this->zero();
    }

    Vector::Vector(RKfloat x, RKfloat y, RKfloat z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector::~Vector()
    {
    }

    Vector Vector::operator+(const Vector &vector) const
    {
        return Vector(this->x + vector.x, this->y + vector.y, this->z + vector.z);
    }

    Vector Vector::operator-(const Vector &vector) const
    {
        return Vector(this->x - vector.x, this->y - vector.y, this->z - vector.z);
    }

    Vector &Vector::operator+=(const Vector &vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        this->z += vector.z;

        return *this;
    }

    Vector &Vector::operator-=(const Vector &vector)
    {
        this->x -= vector.x;
        this->y -= vector.y;
        this->z -= vector.z;

        return *this;
    }

    Vector Vector::operator/(const RKfloat &scalar) const
    {
        return Vector(this->x / scalar, this->y / scalar, this->z / scalar);
    }

    Vector Vector::operator*(const RKfloat &scalar) const
    {
        return Vector(this->x * scalar, this->y * scalar, this->z * scalar);
    }

    Vector &Vector::operator/=(const RKfloat &scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;

        return *this;
    }

    Vector &Vector::operator*=(const RKfloat &scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;

        return *this;
    }

    RKfloat Vector::length() const
    {
        RKfloat length = this->x * this->x + this->y * this->y + this->z * this->z;

        return sqrtf(length);
    }

    Vector Vector::normal() const
    {
        RKfloat length = this->length();

        if (length == 0.0f)
        {
            return *this;
        }

        return (*this / length);
    }

    Vector &Vector::normalize()
    {
        RKfloat length = this->length();

        return (*this /= length);
    }

    Vector &Vector::zero()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;

        return *this;
    }
}