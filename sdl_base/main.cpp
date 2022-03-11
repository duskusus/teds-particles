#include "gUtil.h"
#include "util.h"
#include <cmath>
#include <iostream>

extern Fbuffer *_SCREEN;
extern bool _RUNNING;

int main(int argc, char **argv) {
  bool running = true;
  Fbuffer s = init(1280, 720, "");
  _SCREEN = &s;
  int clicks = 0;
  vec2 vertices[3];
  vec2 lmouse = vec2(0, 0);
  float cursor_radius = 0.01;
  bool show_cursor = false;

  while (_RUNNING) {
    if(show_cursor){
      if((mouse()-lmouse).len() > 0.0001)s.circle(Color(0, 0, 0), lmouse, cursor_radius);
      s.circle(Color(0, 1, 0), mouse(), cursor_radius);
      lmouse = mouse();
    }

    if (clickCheck()) {
      vertices[clicks] = mouse();
      clicks ++;
      if (clicks == 3) {
        s.ntri(Color(1, 1, 1), vertices[0], vertices[1], vertices[2]);
        clicks = 0;
      }
    }
    s.present();
    poll();
  }
  quit();
  return 0;
}
