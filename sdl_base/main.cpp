#include "util.h"
#include "primitives.h"
#include <cmath>
#include <iostream>
extern bool _RUNNING;
int main(int argc, char **argv)
{
    bool running = true;
    Fbuffer *s = init(1280, 720, "");
    while (_RUNNING)
    {
	for(int x = 0; x < _WIDTH; x++){
		for(int y = 0; y < _HEIGHT; y++){
			s->tri(0, 1, 1);
		}
	}
        present();
        poll();

    }
    quit();
    return 0;
}
