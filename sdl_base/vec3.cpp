#include "vec3.h"
#include <cmath>
vec3::vec3(float _x, float _y, float _z)
{
    x = _x;
    y = _x;
    z = _z;
}
vec3 vec3::operator+(vec3 b)
{
    return vec3(x + b.x, y + b.y, z + b.z);
}
vec3 vec3::operator-(vec3 b)
{
    return vec3(x - b.x, y - b.y, z - b.z);
}
vec3 vec3::operator*(float f)
{
    return vec3(x * f, y * f, z * f);
}
vec3 vec3::operator/(float f)
{
    return vec3(x / f, y / f , z / f);
}