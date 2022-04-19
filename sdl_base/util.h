#pragma once
#include <SDL2/SDL.h>
#include "gUtil.h"
extern bool _RUNNING;
//graphics and image manipulation functions should operate directly on floating point color objects, hence no getf function.

vec2 mouse();
uint32_t *lock();
void present();
void quit();
void poll();
Fbuffer init(int width, int height, const char *name);
bool clickCheck();
float frand(float min = 0, float max = 1);
vec2 vec2rand();
