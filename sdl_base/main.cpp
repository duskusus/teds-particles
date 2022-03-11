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
  while (_RUNNING) {
    s.circle(Color(0, 1, 0), mouse(), 0.1);
    if((mouse()-lmouse).len() > 0.0001)s.circle(Color(0, 0, 0), lmouse, 0.1);
    lmouse = mouse();
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
