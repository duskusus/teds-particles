#pragma once
#include "vec2.h"
#include "vec3.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <stdint.h>


extern unsigned int _WIDTH;
extern unsigned int _HEIGHT;
class Color {
public:
  uint32_t _ICOLOR;
  void seti(uint32_t color);
  void set(float r, float g, float b);
  uint32_t getInt();
  Color(float r = 0.0, float g = 0.0, float b = 0.0);
};
class Fbuffer {
public:
  Color *buffer;
  SDL_Texture *texture;
  SDL_Renderer *renderer;
  unsigned int pitch;
  unsigned int buffer_size;
  bool debugging_circles = true;

  Fbuffer(unsigned int width, unsigned int height, SDL_Window *window);
  void set(vec2 pos, Color c);
  void set(unsigned int x, unsigned int y, Color c);
  unsigned int get(unsigned int pos);
  Color &get(vec2);
  Color &get(unsigned int x, unsigned int y);
  int sign(int x);
  void clear(Color c);
  void line(Color c, vec2 pos1, vec2 pos2);
  void iline(Color c, vec2 pos1, vec2 pos2);
  void tri(Color col, vec2 a, vec2 b, vec2 c);
  void ftri(Color fill, vec2 a, vec2 b, vec2 c);
  void ntri(Color fill, vec2 a, vec2 b, vec2 c);
  void circle(Color fill, vec2 center, float r);
  void present();
};