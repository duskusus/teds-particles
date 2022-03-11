#include "gUtil.h"
#include <cmath>
#include <iostream>

inline vec2 greaterx(vec2 a, vec2 b) { return (a.intx() > b.intx()) ? a : b; }
inline vec2 lesserx(vec2 a, vec2 b) { return (a.intx() < b.intx()) ? a : b; }
inline vec2 greaterx(vec2 a, vec2 b, vec2 c) {
  return greaterx(greaterx(a, b), c);
}
inline vec2 lesserx(vec2 a, vec2 b, vec2 c) {
  return lesserx(lesserx(a, b), c);
}
inline vec2 midx(vec2 a, vec2 b, vec2 c) {
  return lesserx(greaterx(a, b), greaterx(b, c), greaterx(a, c));
}
inline vec2 greatery(vec2 a, vec2 b) { return (a.inty() > b.inty()) ? a : b; }
inline vec2 lessery(vec2 a, vec2 b) { return (a.inty() < b.inty()) ? a : b; }
inline vec2 greatery(vec2 a, vec2 b, vec2 c) {
  return greatery(greatery(a, b), c);
}
inline vec2 lessery(vec2 a, vec2 b, vec2 c) {
  return lessery(lessery(a, b), c);
}
inline vec2 midy(vec2 a, vec2 b, vec2 c) {
  return lessery(greatery(a, b), greatery(b, c), greatery(a, c));
}

void Fbuffer::ntri(Color fill, vec2 a, vec2 b, vec2 c) {

  vec2 top;
  vec2 middle;
  vec2 bottom;
  // ftri(Color(0, 1, 0), a, b, c);

  float radius = 0.01; // for debugging circles

  bool h_edge =
      a.intx() == b.intx() || a.intx() == c.intx() || c.intx() == b.intx();
  bool v_edge =
      a.inty() == b.inty() || a.inty() == c.inty() || c.inty() == b.inty();

  if (h_edge && v_edge) {
    std::cout << "both!! render time\n";
    top = greatery(a, b, c);
    bottom = lessery(a, b, c);
    vec2 right = greaterx(a, b, c);
    vec2 left = lesserx(a, b, c);

    int height = top.inty() - bottom.inty();
    int width = right.intx() - left.intx();
    for(int y = 0; y < height; y++) {
        int w = 0;
        for(int x = 0; x < w; x++) {
            set(x + left, y + bottom);
        }

    }
  } else if (v_edge) {

    std::cout << "vertical edge\n";
    // broken up into smaller triangles

    top = greatery(a, b, c);
    middle = midy(a, b, c);
    bottom = lessery(a, b, c);

    // top triangle vertices
    vec2 t_a, t_b, t_c;
    // bottom triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth, splitting point, intersection of y = mid.y and line from
    // top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    std::cout << "slope " << slope << std::endl;
    float new_x =
        (middle.y - bottom.y) * (bottom.x - top.x) / (bottom.y - top.y) +
        bottom.x;

    // top triangle

    t_a = top;
    t_b = middle;
    t_c = vec2(new_x, middle.y);

    std::cout << "top " << top.about() << "\nmid " << middle.about()
              << "\nbottom " << bottom.about() << "\nsplit " << t_c.about()
              << std::endl;

    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    ntri(Color(1, 0, 0), t_a, t_b, t_c);
    ntri(Color(0, 0, 1), b_a, b_b, b_c);

    if (debugging_circles) {
      circle(Color(0, 0, 1), t_a, radius);
      circle(Color(0, 1, 0), t_c, radius);
      circle(Color(1, 0, 0), t_b, radius);

      circle(Color(0, 1, 1), b_a, radius);
      circle(Color(1, 1, 0), b_c, radius);
      circle(Color(1, 0, 1), b_b, radius);

      circle(Color(0, 1, 0), middle, radius);
    }
  } else if (h_edge) {

    std::cout << "horizontal edge\n";

    bottom = lesserx(a, b, c);
    middle = midx(a, b, c);
    top = greaterx(a, b, c);

    // broken up into smaller triangles

    top = greaterx(a, b, c);
    middle = midx(a, b, c);
    bottom = lesserx(a, b, c);

    // right triangle vertices
    vec2 t_a, t_b, t_c;
    // left triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth vertex , splitting point, intersection of x = middle.x and
    // line from top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    std::cout << "slope " << slope << std::endl;
    float new_x =
        (middle.y - bottom.y) * (bottom.x - top.x) / (bottom.y - top.y) +
        bottom.x;

    // top triangle

    t_a = top;
    t_b = middle;
    t_c = vec2(new_x, middle.y);

    std::cout << "top " << top.about() << "\nmid " << middle.about()
              << "\nbottom " << bottom.about() << "\nsplit " << t_c.about()
              << std::endl;

    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    ntri(Color(1, 0, 0), t_a, t_b, t_c);
    ntri(Color(0, 0, 1), b_a, b_b, b_c);

    if (debugging_circles) {
      circle(Color(0, 0, 1), t_a, radius);
      circle(Color(0, 1, 0), t_c, radius);
      circle(Color(1, 0, 0), t_b, radius);

      circle(Color(0, 1, 1), b_a, radius);
      circle(Color(1, 1, 0), b_c, radius);
      circle(Color(1, 0, 1), b_b, radius);

      circle(Color(0, 1, 0), middle, radius);
    }

    set(middle, Color(0, 1, 0));
  } else {
    std::cout << "neither\n";
    // broken up into smaller triangles

    top = greatery(a, b, c);
    middle = midy(a, b, c);
    bottom = lessery(a, b, c);

    // top triangle vertices
    vec2 t_a, t_b, t_c;
    // bottom triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth, splitting point, intersection of y = mid.y and line from
    // top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    std::cout << "slope " << slope << std::endl;
    float new_x =
        (middle.y - bottom.y) * (bottom.x - top.x) / (bottom.y - top.y) +
        bottom.x;

    // top triangle

    t_a = top;
    t_b = middle;
    t_c = vec2(new_x, middle.y);

    std::cout << "top " << top.about() << "\nmid " << middle.about()
              << "\nbottom " << bottom.about() << "\nsplit " << t_c.about()
              << std::endl;

    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    ntri(Color(1, 0, 0), t_a, t_b, t_c);
    ntri(Color(0, 0, 1), b_a, b_b, b_c);

    if (debugging_circles) {
      circle(Color(0, 0, 1), t_a, radius);
      circle(Color(0, 1, 0), t_c, radius);
      circle(Color(1, 0, 0), t_b, radius);

      circle(Color(0, 1, 1), b_a, radius);
      circle(Color(1, 1, 0), b_c, radius);
      circle(Color(1, 0, 1), b_b, radius);

      circle(Color(0, 1, 0), middle, radius);
    }
  }
}
  void Fbuffer::tri(Color col, vec2 a, vec2 b, vec2 c) {
    iline(col, a, b);
    iline(col, b, c);
    iline(col, c, a);
  }
  void Fbuffer::circle(Color fill, vec2 center, float r) {
    float w = float(_HEIGHT);
    r *= w;
    for (int x = r * -1; x < r; x++) {
      int hh = r * r - x * x;
      int h = sqrt(hh);
      // std::cout << "x: " << x << " hh: " << hh << std::endl;
      for (int y = 0 - h; y < 0 + h; y++) {

        set(x + center.intx(), y + center.inty(), fill);
      }
    }
  }
  void Fbuffer::ftri(Color fill, vec2 a, vec2 b, vec2 c) {
    float precision = 700;
    vec2 d = b - a;
    vec2 e = b - c;
    d = d / d.len();
    e = e / e.len();
    d = d / precision;
    e = e / precision;

    vec2 x = a;
    vec2 y = c;
    while ((x - b).len() > 1 / precision && (y - b).len() > 1 / precision) {
      iline(fill, x, y);
      x = x + d;
      y = y + e;
    }
    tri(fill, a, b, c);
}