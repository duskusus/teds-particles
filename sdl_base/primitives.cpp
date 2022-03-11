#include "gUtil.h"
#include <iostream>
#include <cmath>
void Fbuffer::ntri(Color fill, vec2 a, vec2 b, vec2 c)
{
    vec2 top;
    vec2 middle;
    vec2 bottom;
    set(middle, Color(0, 1, 0));
    if(a.intx() == b.intx() || a.intx() == c.intx() || c.intx() == b.intx()) {
        std::cout << "horizontal edge\n";
        middle = (a.inty() > b.inty()) ? a : b;
        middle = (middle.inty() > c.inty()) ? c : middle;
        
        set(middle, Color(0, 1, 0));
    } else if(a.inty() == b.inty() || a.inty() == c.inty() || c.inty() == b.inty()) {
        std::cout << "vertical edge\n";

        middle = (a.intx() > b.intx()) ? a : b;
        middle = (middle.intx() > c.intx()) ? c : middle;
        
        set(middle, Color(0, 1, 0));
    } else {
        std::cout << "neither\n";
        //these are broken up vertically into smaller triangles
        top = (a.inty() > b.inty()) ? a : b;
        top = (top.inty() > c.inty()) ? top : c;

        bottom = (a.inty() < b.inty()) ? a : b;
        bottom = (bottom.inty() < c.inty()) ? bottom : c;

        if(a.inty() > bottom.inty() && a.inty() < top.inty()) {
            middle = a;
        } else if(b.inty() > bottom.inty() && b.inty() < top.inty()) {
            middle = b;
        } else if(c .inty () > bottom.inty() && b.inty () < top.inty()){
            middle = c;
        }

        //top triangle vertices
        vec2 t_a, t_b, t_c;
        //bottom triangle vertices
        vec2 b_a, b_b, b_c;

        //top triangle
        t_a = top;
        t_b = middle;
        t_c = (top-middle).proj_on(top-bottom) + top;
        ftri(Color(1, 0, 0), t_a, t_b, t_c);
        float radius = 0.1;
        circle(Color(0, 0, 1), t_a, radius);
        circle(Color(0, 1, 1), t_c, radius);
        circle(Color(0, 1, 0), t_b, radius);
        //bottom triangle
        b_a = bottom;
        b_b = middle;
        b_c = t_c;
        ftri(Color(0, 0, 1), b_a, b_b, b_c);
    }
}
void Fbuffer::tri( Color col, vec2 a, vec2 b, vec2 c)
{
    iline(col, a, b);
    iline(col, b, c);
    iline(col, c, a);
}
void Fbuffer::circle(Color fill, vec2 center, float r)
{
    float w = float(_HEIGHT);
    r *= w;
    for(int x = r * -1 ; x < r; x++)
    {
        int hh = r * r - x * x;
        int h = sqrt(hh);
        std::cout << "x: " << x << " hh: " << hh << std::endl;
        for(int y = 0-h; y < 0 + h; y++) {
            
            set(x + center.intx(), y + center.inty(), fill);
        }
    }
}
void Fbuffer::ftri( Color fill, vec2 a, vec2 b, vec2 c)
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
        iline(fill, x, y);
        x = x + d;
        y = y + e;
    }
    tri(fill, a, b, c);
}