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

  vec2 top;
  vec2 middle;
  vec2 bottom;
  // ftri(Color(0, 1, 0), a, b, c);

  float radius = 0.01; // for debugging circles
  std::cout << "\n\n";
  bool v_edge =
      a.intx() == b.intx() || a.intx() == c.intx() || b.intx() == c.intx();
  bool h_edge =
      a.inty() == b.inty() || a.inty() == c.inty() || c.inty() == b.inty();

  if (h_edge && v_edge) {
    std::cout << "both\n";
    std::cout << a.about() << " " << b.about() << " " << c.about() << std::endl;
    // ftri(fill, a, b, c);
    vec2 vx[] = {a, b, c};
    sortx(vx);
    vec2 vy[] = {a, b, c};
    sorty(vy);
    int dx = (vx[2] - vx[0]).intx();
    int dy;
    if(vx[0].intx() == vx[1].intx()) {
      //we know vertical edge is on the left
      vec2 extreme = (vx[0].inty() == vx[2].inty()) ? vx[1] : vx[0];
      dy = (vx[2] - extreme).inty();
    } else if(vx[1].intx() == vx[2].intx()) {
      //we know vertical edge is on the right
      vec2 extreme = (vx[1].inty() == vx[0].inty()) ? vx[2] : vx[1];
      dy = (extreme - vx[0]).inty();
    }
    float slope = float(dy) / float(dx);
    std::cout << "dx " << dx << " dy " << dy << " slope " << slope << std::endl;
    for(int x = 0; x < dx; x ++) {
      int h = vx[0].inty() + slope * x;
      for(int y = 0; y * y < h * h; y += sign(dy)) {
        set(x + vx[0].intx(), vx[0].y - y, fill);
      }
    }
    tri(Color(1, 1, 1), a, b, c);
  } else if (h_edge) {

    std::cout << "horizontal edge\n";
    // broken up into smaller triangles
    // sort by x
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
    std::cout << "slope " << slope << std::endl;
    float new_y = slope * middle.x + k;
    if (middle.x < top.x && middle.x > bottom.x)

      // top triangle

      t_a = top;
    t_b = middle;
    t_c = vec2(middle.x, new_y);

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
  } else if (v_edge) {

    std::cout << "vertical edge\n";
    // sort by y
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
    std::cout << "slope " << slope << std::endl;
    float new_x = (middle.y - k) / slope;

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

    // ntri(Color(1, 0, 0), t_a, t_b, t_c);
    // ntri(Color(0, 0, 1), b_a, b_b, b_c);

    ntri(Color(1, 0, 0), t_a, t_b, t_c);
    ntri(Color(0, 1, 0), b_a, b_b, b_c);

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