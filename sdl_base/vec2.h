#pragma once
class vec2{
    public:
    float x = 0.0;
    float y = 0.0;
    unsigned int intx();
    unsigned int inty();
    unsigned int index();
    vec2(float x = 0.0, float y = 0.0);
    vec2 operator+(vec2 b);
    vec2 operator-(vec2 b);
    float operator*(vec2 b);
    vec2 operator*(float f);
    vec2 operator/(float f);
    vec2 proj_on(const vec2 &p);
    float len();
};