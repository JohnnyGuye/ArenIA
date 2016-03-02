/*
 *  Vector3D by Johnny
 */

#ifndef w_Vector3
#define w_Vector3

#include <cmath>


class Vector3
{
public:
                float X;
                float Y;
                float Z;

                //Vector3();
                Vector3(float x = 0, float y = 0, float z = 0);

                Vector3         operator+(const Vector3& other) const;
                Vector3         operator-(const Vector3& other) const;
                Vector3         operator-() const;
                Vector3         operator*(const float num) const;
                Vector3         operator/(const float num) const;

                Vector3&         operator=(const Vector3& other);

                Vector3&        operator+=(const Vector3& other);
                Vector3&        operator-=(const Vector3& other);
                Vector3&        operator*=(float num);
                Vector3&        operator/=(float num);

                bool            operator==(const Vector3& other) const;
                bool            operator!=(const Vector3& other) const;

                Vector3& normalize();
                Vector3 crossProduct(const Vector3 & other) const;
                float scalarProduct(const Vector3 & other) const;
                float length() const;

                //static const Vector3 Zero = Vector3(0.f, 0.f, 0.f);
                //static const float     Epsilon = 0.000000001f;
        };
#endif
