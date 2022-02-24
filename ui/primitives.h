#pragma once
#include <future>
#include "gUtil.h"
#include "vec2.h"
#include "vec3.h"
void line(Fbuffer *f, Color c, vec2 pos1, vec2 pos2);
void iline(Fbuffer *f, Color c, vec2 pos1, vec2 pos2);
void tri(Fbuffer *f, Color col, vec2 a, vec2 b, vec2 c);
void ftri(Fbuffer *f, Color fill, vec2 a, vec2 b, vec2 c);
