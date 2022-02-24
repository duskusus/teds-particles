#include "vec2.h"
#include "util.h"
vec2 vec2::operator+(vec2 b)
{
    return vec2(x + b.x, y + b.y);
}
vec2 vec2::operator-(vec2 b)
{
    return vec2(x - b.x, y - b.y);
}
float vec2::operator*(vec2 b)
{
    return x * b.x + y * b.y;
}
vec2 vec2::operator*(float f)
{
    return vec2(x * f, y * f);
}
vec2 vec2::operator/(float f)
{
    return vec2(x / f, y / f);
}
float vec2::len()
{
    return hypot(x, y);
}
unsigned int vec2::intx()
{
    return (x + 1.0) * float(_WIDTH) / 2.0;
}
unsigned int vec2::inty()
{
    return (1.0 - y) * float(_HEIGHT) / 2.0;
}
unsigned int vec2::index()
{
    return intx() + inty() * _WIDTH;
}
vec2::vec2(float _x, float _y)
{
    x = _x;
    y = _y;
}