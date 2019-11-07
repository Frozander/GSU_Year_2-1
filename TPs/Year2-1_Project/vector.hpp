#ifndef __VECT_H
#define __VECT_H

#include <cmath>

class Vec3
{
private:
    float x, y ,z;
public:
    Vec3(float x , float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator +(Vec3 vec)
    {
        return Vec3(x + vec.x, y + vec.y, z + vec.z);
    }

    Vec3 operator -(Vec3 vec)
    {
        return Vec3(x - vec.x, y - vec.y, z - vec.z);
    }

    Vec3 operator *(float scalar)
    {
        return Vec3(scalar * x, scalar * y, scalar * z);
    }

    float dot(Vec3 vec)
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    float norm()
    {
        return sqrt(dot(*this));
    }

    Vec3 normalize()
    {
        return (*this)*(1/norm());
    }
    
};

#endif