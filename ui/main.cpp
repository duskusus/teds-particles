#include "util.h"
#include "primitives.h"
#include <cmath>
#include <iostream>
extern bool _RUNNING;
int main(int argc, char **argv)
{
    bool running = true;
    Fbuffer *screen = init(1280, 720, "aaaa");
    while (_RUNNING)
    {
        for(float j = -1.0; j < 1.0; j += 2.0 / float(1280))
        {
            for(float i = -1.0; i < 1.0; i+= 2.0 / float(720))
            {
                screen->set(vec2(j, i), Color(j/2 + 0.5, i/2 + 0.5, 0.25));
            }
        }
        present();
        poll();

    }
    quit();
    return 0;
}
