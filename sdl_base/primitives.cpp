#include "gUtil.h"
#include "primitives.h"
#include <iostream>
int sign(int x)
{
    if(x >= 0){
        return 1;
    }else{
        return -1;
    }

}
void line(Fbuffer *f, Color c, vec2 pos1, vec2 pos2)
{
    const float precision = 600;
    vec2 d = pos2 - pos1;
    if (d.len() == 0.0)
        return;
    d = d / d.len();
    d = d / precision;
    //std::cout << "dx: " << d.x << " dy: " << d.y <<  std::endl;
    vec2 e = pos1;
    while ((pos2 - e).len() > 1 / precision)
    {
        e = e + d;
        f->set(e, c);
        //std::cout << "e.x: " << e.x << " e.y: " << e.y << std::endl;
    }
}
void iline(Fbuffer *f, Color c, vec2 pos1, vec2 pos2)
{
    int x1 = pos1.intx();
    int x2 = pos2.intx();
    int y1 = pos1.inty();
    int y2 = pos2.inty();
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) < abs(dx))
    {

        for (int t = 0; abs(t) < abs(dx); t+= sign(dx))
        {
            int fx = t * dy + y1 * dx;
            fx = fx / dx;
            f->set(t + x1, fx, c);
        }
    }else{
        for(int t = 0; abs(t) < abs(dy); t+= sign(dy))
        {
            int fy = t * dx + x1 * dy;
            fy = fy / dy;
            f->set(fy, t + y1, Color(1, 0, 0));
        }
    }
}
void tri(Fbuffer *f, Color col, vec2 a, vec2 b, vec2 c)
{
    line(f, col, a, b);
    line(f, col, b, c);
    line(f, col, c, a);
}
void ftri(Fbuffer *f, Color fill, vec2 a, vec2 b, vec2 c)
{
    float precision = 700;
    vec2 d = b - a;
    vec2 e = b - c;
    d = d / d.len();
    e = e / e.len();
    d = d / precision;
    e = e / precision;

    vec2 x = a;
    vec2 y = c;
    while ((x - b).len() > 1 / precision && (y - b).len() > 1 / precision)
    {
        iline(f, fill, x, y);
        x = x + d;
        y = y + e;
    }
    tri(f, Color(1, 1, 1), a, b, c);
}