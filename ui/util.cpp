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
Fbuffer *_SCREEN;
Color *_FPIXELS;

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
Fbuffer *init(int width, int height, const char *name)
{
    SDL_Init(SDL_INIT_VIDEO);
    _WIN = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    _REN = SDL_CreateRenderer(_WIN, -1, SDL_RENDERER_SOFTWARE);
    _TEX = SDL_CreateTexture(_REN, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
    _RUNNING = true;
    _WIDTH = width;
    _HEIGHT = height;
    _PITCH = _WIDTH * 3;
    _SCREEN = new Fbuffer(_WIDTH, _HEIGHT);
    return _SCREEN;
}
void present()
{
    static std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
    uint32_t *_IPIXELS;
    //if you impliment a depth buffer, maybe do it here
    SDL_LockTexture(_TEX, nullptr, (void **)&_IPIXELS, (int *)&_PITCH);
    for (int i = 0; i < _WIDTH * _HEIGHT; i++)
    {
        _IPIXELS[i] = _SCREEN->get(i);
    }
    SDL_UnlockTexture(_TEX);
    SDL_RenderCopy(_REN, _TEX, NULL, NULL);
    SDL_RenderPresent(_REN);
    unsigned int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last).count();
    last = std::chrono::steady_clock::now();
    if(elapsed < 16){
        SDL_Delay(16 - elapsed);
    }
    
    std::cout << elapsed << std::endl;
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
            switch(e.key.keysym.sym){
                case SDLK_c:
                    _SCREEN->clear(Color(0, 0, 0));
            }
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