#include "Vector3.h"

Vector3::Vector3(float x , float y, float z)
:X(x), Y(y), Z(z)
{}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-X, -Y, -Z);
}

Vector3 Vector3::operator*(const float num) const
{
    return Vector3(X * num, Y * num, Z * num);
}

Vector3 Vector3::operator/(const float num) const
{
    return Vector3(X/num, Y/num, Z/num);
}

Vector3& Vector3::operator=(const Vector3& other)
{
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    return *this;
}

Vector3& Vector3::operator*=(const float num)
{
    X *= num;
    Y *= num;
    Z *= num;
    return *this;
}

Vector3& Vector3::operator/=(const float num)
{
    X /= num;
    Y /= num;
    Z /= num;
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
        return (other.X == X && other.Y == Y && other.Z == Z);
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !(*this == other);
}

Vector3& Vector3::normalize()
{
    return ((*this)/=length());
}

float Vector3::length() const
{
    return sqrt(X * X + Y * Y + Z * Z);
}

Vector3 Vector3::crossProduct(const Vector3 & other) const
{
    return Vector3(X * other.Y - Y * other.X, Y * other.Z - Z * other.Y, Z * other.X - X * other.Z);
}

float Vector3::scalarProduct(const Vector3 & other) const
{
    return (other.X * X + other.Y * Y + other.Z * Z);
}

