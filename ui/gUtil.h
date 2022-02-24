#pragma once
#include <stdint.h>
#include <cmath>
#include "vec2.h"
extern unsigned int _WIDTH;
extern unsigned int _HEIGHT;
class Color{
    public:
    uint32_t _ICOLOR;
    void seti(uint32_t color);
    void set(float r, float g, float b);
    uint32_t getInt();
    Color(float r = 0.0, float g = 0.0, float b = 0.0);
};
class Fbuffer{
    public:
    Color *buffer;
    unsigned int buffer_size;
    Fbuffer(unsigned int width, unsigned int height);
    void set(vec2 pos, Color c);
    void set(unsigned int x, unsigned int y, Color c);
    unsigned int get(unsigned int pos);
    void clear(Color c);

};