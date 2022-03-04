#include "util.h"
#include <iostream>
#include <vector>
#include <chrono>
bool _RUNNING = false;
vec2 _MOUSEPOS;
bool _CLICKED;
SDL_Window *_WIN;
SDL_Renderer *_REN;
SDL_Texture *_TEX;
unsigned int _PITCH;
unsigned int _WIDTH = 0;
unsigned int _HEIGHT = 0;
Color *_FPIXELS;
Fbuffer *_SCREEN;

vec2 mouse(){
    vec2 fmouse(2.0 * _MOUSEPOS.x / float(_WIDTH) - 1.0, 1.0 - (2.0 * _MOUSEPOS.y / float(_HEIGHT)));
    //correct method of converting int screenspace to floating point ndc
    return fmouse;
}
bool clickCheck()
{
    bool ph = _CLICKED;
    _CLICKED = false;
    return ph;
}
Fbuffer init(int width, int height, const char *name)
{
    SDL_Init(SDL_INIT_VIDEO);
    _WIN = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    _RUNNING = true;
    _WIDTH = width;
    _HEIGHT = height;
    _PITCH = _WIDTH * 3;
    Fbuffer f(_WIDTH, _HEIGHT, _WIN);
    return f;
}
void quit()
{
    SDL_DestroyRenderer(_REN);
    SDL_DestroyWindow(_WIN);
    SDL_Quit();
    delete[] _FPIXELS;
    return;
}
void poll()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            _RUNNING = false;
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            _MOUSEPOS.x = e.motion.x;
            _MOUSEPOS.y = e.motion.y;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            //handle keyboard events here with a switch on e.key.sym.keysym (or something)
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            _CLICKED = true;
        }
    }
}

/*int pain(int argc, char **argv)
{
    int width = 640;
    int height = 480;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("SDLBaseProject", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
    bool quit = false;
    uint32_t *pixels = nullptr;
    int pitch = NULL;
    while(!quit)
    {
         SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        std::cout << "drawing\n";
        SDL_LockTexture(tex, nullptr, (void**)&pixels, &pitch);
        for(unsigned int i = 1; i < width * height; i++)
        {
           pixels[i] = i %  255;
        }
        std::cout << "done drawing\n";
        SDL_UnlockTexture(tex);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}*/