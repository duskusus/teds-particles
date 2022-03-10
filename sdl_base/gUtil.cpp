#include "gUtil.h"
#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
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
Fbuffer::Fbuffer(unsigned int width, unsigned int height, SDL_Window *window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
 
    buffer = new Color[width * height];
    buffer_size = width * height;
}
void Fbuffer::set(vec2 pos, Color c)
{
    unsigned int i = pos.index();
    if(i < buffer_size)
        buffer[i] = c;
}
void Fbuffer::present()
{
    static std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
    uint32_t *_IPIXELS;
    //if you impliment a depth buffer, maybe do it here
    SDL_LockTexture(texture, nullptr, (void **)&_IPIXELS, (int *)&pitch);
    for (int i = 0; i < _WIDTH * _HEIGHT; i++)
    {
        _IPIXELS[i] = get(i);
    }
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    unsigned int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last).count();
    last = std::chrono::steady_clock::now();
    if(elapsed < 16){
        SDL_Delay(16 - elapsed);
    }
    
    std::cout << elapsed << std::endl;
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
int Fbuffer::sign(int x)
{
    if(x >= 0){
        return 1;
    }else{
        return -1;
    }

}

