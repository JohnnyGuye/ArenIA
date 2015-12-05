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
                Vector3         operator*(float num) const;
                Vector3         operator/(float num) const;

                Vector3&         operator=(const Vector3& other);

                Vector3&        operator+=(const Vector3& other);
                Vector3&        operator-=(const Vector3& other);
                Vector3&        operator*=(float num);
                Vector3&        operator/=(float num);

                bool            operator==(const Vector3& other) const;
                bool            operator!=(const Vector3& other) const;

                static const Vector3 Zero;
                static const float     Epsilon;
        };
#endif
