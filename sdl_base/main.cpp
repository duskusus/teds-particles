#include "gUtil.h"
#include "util.h"
#include <cmath>
#include <iostream>
#include <exception>
#include "triangle.h"
#include <vector>
#include <chrono>

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
  std::vector<Triangle> triangles;
  while (_RUNNING) {
    if (show_cursor) {
      if ((mouse() - lmouse).len() > 0.0001)
        s.circle(Color(0, 0, 0), lmouse, cursor_radius);
      s.circle(Color(0, 1, 0), mouse(), cursor_radius);
      lmouse = mouse();
    }
    triangles.emplace_back(Triangle(vec2rand(), vec2rand(), vec2rand(), Color(frand(), frand(), frand())));
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    for(Triangle t : triangles) {
      s.ntri(t.fill, t.a, t.b, t.c);
    }
    std::cout << "size " << triangles.size() << " time " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    s.present();
    s.clear(Color(0, 0, 0));
    poll();
  }
  quit();
  return 0;
}
