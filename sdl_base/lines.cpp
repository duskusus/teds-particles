#include "gUtil.h"
void Fbuffer::line( Color c, vec2 pos1, vec2 pos2)
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
        set(e, c);
        //std::cout << "e.x: " << e.x << " e.y: " << e.y << std::endl;
    }
}
void Fbuffer::iline( Color c, vec2 pos1, vec2 pos2)
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
            set(t + x1, fx, c);
        }
    }else{
        for(int t = 0; abs(t) < abs(dy); t+= sign(dy))
        {
            int fy = t * dx + x1 * dy;
            fy = fy / dy;
            set(fy, t + y1, c);
        }
    }
}