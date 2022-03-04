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
  while (_RUNNING) {
    s.clear(Color(0, 0, 0));
    s.ftri(Color(1.0, 1.0, 1.0), vec2(0.0, 0.0), vec2(0.0, 0.5 + mouse().len()) + mouse(), mouse());
    s.present();
    poll();
  }
  quit();
  return 0;
}
