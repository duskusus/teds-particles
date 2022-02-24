class vec3{
    float x;
    float y;
    float z;
    vec3(float x = 0, float y = 0, float z = 0);
    vec3 operator+(vec3 b);
    vec3 operator-(vec3 b);
    vec3 operator*(float f);
    vec3 operator/(float f);
};