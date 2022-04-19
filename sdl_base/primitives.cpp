#include "gUtil.h"
#include <cmath>
#include <iostream>
void flip(vec2 *a, vec2 *b) {
  vec2 temp = *a;
  *a = *b;
  *b = temp;
}
void sorty(vec2 *vs) {
  // returns vertices sorted in ascending order by y value
  if (vs[0].y > vs[1].y) {
    flip(&vs[0], &vs[1]);
  }
  if (vs[1].y > vs[2].y) {
    flip(&vs[1], &vs[2]);
  }
  if (vs[0].y > vs[1].y) {
    flip(&vs[0], &vs[1]);
  }
  if (vs[0].y > vs[1].y || vs[1].y > vs[2].y) {
    std::cout << "sorting failed" << std::endl;
  }
}
void Fbuffer::rtri(vec2 center, float dx, float dy) {
  float slope = dy / dx;
  for (int x = center.intx(); x < dx * sign(dx); x++) {
    int h = center.inty() - sign(dx) * slope * x;
    for (int y = 0; y < h * sign(dy); y += sign(dy)) {
      set(x, y, Color(1, 0, 0));
    }
  }
}
void sortx(vec2 *vs) {
  // returns vertices sorted in ascending order bx x value
  if (vs[0].x > vs[1].x) {
    flip(&vs[0], &vs[1]);
  }
  if (vs[1].x > vs[2].x) {
    flip(&vs[1], &vs[2]);
  }
  if (vs[0].x > vs[1].x) {
    flip(&vs[0], &vs[1]);
  }
  if (vs[0].x > vs[1].x || vs[1].x > vs[2].x) {
    std::cout << "sorting failed" << std::endl;
  }
}
void Fbuffer::ntri(Color fill, vec2 a, vec2 b, vec2 c) {

  int min_size = 10;
  vec2 vx[] = {a, b, c};
  sortx(vx);
  vec2 vy[] = {a, b, c};
  sorty(vy);
  vec2 top = vy[2];
  vec2 middle = vy[1];
  vec2 bottom = vy[0];
  if(vx[2].intx() - vx[0].intx() < min_size  || vy[2].inty() - vy[0].inty() < min_size) return;
  // ftri(Color(0, 1, 0), a, b, c);

  float radius = 0.01; // for debugging circles
  bool v_edge =
      a.intx() == b.intx() || a.intx() == c.intx() || b.intx() == c.intx();
  bool h_edge =
      a.inty() == b.inty() || a.inty() == c.inty() || c.inty() == b.inty();

  if (h_edge && v_edge) {
    vec2 center(vx[1].x, vy[1].y);
    int dx = ((center.intx() == vx[0].intx()) ? vx[2].intx() : vx[0].intx()) - center.intx();
    int dy = ((center.inty() == vy[0].inty()) ? vy[2].inty() : vy[0].inty()) - center.inty();
    float slope = float(std::abs(dy)) / float(std::abs(dx));
      for (int x = 0; x < std::abs(dx); x++) {
      int h = std::abs(dy) - x * slope + 1;
      for (int y = 0; y < std::abs(h); y++) {
        set(center.intx() + x * sign(dx), center.inty() + y * sign(dy), fill);
      }
    }
  } else if (h_edge) {

    // std::cout << "horizontal edge\n";
    //  broken up into smaller triangles
    //  sort by x
    vec2 vertices[] = {a, b, c};
    sortx(vertices);
    top = vertices[2];
    middle = vertices[1];
    bottom = vertices[0];

    // top triangle vertices
    vec2 t_a, t_b, t_c;
    // bottom triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth, splitting point, intersection of y = mid.y and line from
    // top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    float k = top.y - slope * top.x;
    // std::cout << "slope " << slope << std::endl;
    float new_y = slope * middle.x + k;
    if (middle.x < top.x && middle.x > bottom.x)

      // top triangle

      t_a = top;
    t_b = middle;
    t_c = vec2(middle.x, new_y);
    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    ntri(fill, t_a, t_b, t_c);
    ntri(fill, b_a, b_b, b_c);

    if (debugging_circles) {
      circle(Color(0, 0, 1), t_a, radius);
      circle(Color(0, 1, 0), t_c, radius);
      circle(Color(1, 0, 0), t_b, radius);

      circle(Color(0, 1, 1), b_a, radius);
      circle(Color(1, 1, 0), b_c, radius);
      circle(Color(1, 0, 1), b_b, radius);

      circle(Color(0, 1, 0), middle, radius);
    }
  } else if (v_edge) {

    // std::cout << "vertical edge\n";
    //  sort by y
    vec2 vertices[] = {a, b, c};
    sorty(vertices);
    bottom = vertices[0];
    middle = vertices[1];
    top = vertices[2];

    // broken up into smaller triangles

    // right triangle vertices
    vec2 t_a, t_b, t_c;
    // left triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth vertex , splitting point, intersection of x = middle.x and
    // line from top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    float new_x =
        (middle.y - bottom.y) * (bottom.x - top.x) / (bottom.y - top.y) +
        bottom.x;

    // top triangle

    t_a = top;
    t_b = middle;
    t_c = vec2(new_x, middle.y);

    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    ntri(fill, t_a, t_b, t_c);
    ntri(fill, b_a, b_b, b_c);

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

    // broken up into smaller triangles
    // sort by y
    vec2 vertices[] = {a, b, c};
    sorty(vertices);
    top = vertices[2];
    middle = vertices[1];
    bottom = vertices[0];

    // top triangle vertices
    vec2 t_a, t_b, t_c;
    // bottom triangle vertices
    vec2 b_a, b_b, b_c;

    // finding fourth, splitting point, intersection of y = mid.y and line from
    // top to bottom
    float slope = (bottom.y - top.y) / (bottom.x - top.x);
    float k = top.y - slope * top.x;
    float new_x = (middle.y - k) / slope;

    // top triangle

    t_a = top;
    t_b = middle;
    t_c = vec2(new_x, middle.y);

    // bottom triangle

    b_a = bottom;
    b_b = middle;
    b_c = t_c;

    // ntri(Color(1, 0, 0), t_a, t_b, t_c);
    // ntri(Color(0, 0, 1), b_a, b_b, b_c);

    ntri(fill, t_a, t_b, t_c);
    ntri(fill, b_a, b_b, b_c);

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
  line(col, a, b);
  line(col, b, c);
  line(col, c, a);
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
  float precision = 200;
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