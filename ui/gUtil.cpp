#include "gUtil.h"
void Color::seti(uint32_t c)
{
    _ICOLOR = c;
}
void Color::set(float r, float g, float b)
{
    _ICOLOR = int(b * 255) | int(g * 255) << 8 | int(r * 255) << 16;
}
uint32_t Color::getInt()
{
    return _ICOLOR;
};
Color::Color(float r, float g, float b)
{
    this->set(r, g, b);
}
Fbuffer::Fbuffer(unsigned int width, unsigned int height)
{
    buffer = new Color[width * height];
    buffer_size = width * height;
}
void Fbuffer::set(vec2 pos, Color c)
{
    unsigned int i = pos.index();
    if(i < buffer_size)
        buffer[i] = c;
}
void Fbuffer::set(unsigned int x, unsigned int y, Color c)
{
    unsigned int i = x + y * _WIDTH;
    if(i < buffer_size)
    {
        buffer[i] = c;
    }
}
unsigned int Fbuffer::get(unsigned int pos)
{
    if(pos < buffer_size)
    {
        return buffer[pos].getInt();
    }
    return 0;
}
void Fbuffer::clear(Color c)
{
    uint32_t icolor = c.getInt();
    for(int i = 0; i < buffer_size; i++)
    {
        buffer[i].seti(icolor);
    }
}
