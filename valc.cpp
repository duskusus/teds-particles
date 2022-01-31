#include <iostream>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
template <typename component_type> class vec2 {
  component_type x_component;
  component_type y_component;

public:
  vec2(component_type x, component_type y) {
    x_component = x;
    y_component = y;
  }
  vec2 operator+(const vec2 &b) {
    return vec2(x_component + b.x_component, y_component + b.y_component);
  }
  vec2 operator-(const vec2 &b) {
    return vec2(x_component + b.x_component, y_component + b.y_component);
  }
  std::string text() {
    return "<" + std::to_string(x_component) + ", " +
           std::to_string(y_component) + ">";
  }
};
int main(int argc, char **argv) {
  unsigned int dimensions = 0;
  if (argv[1]) {
    dimensions = atoi(argv[1]);
  } else {
    std::cout << "you must provide a number of dimensions\n";
    return 0;
  }
  std::cout << "using " << dimensions << " dimensions\n";
  bool running = true;
  std::vector<float> scalars;
  std::vector<vec2<float>> vectors;

  while (running) {
    std::string in = "";
    std::cin >> in;
    if (in == "quit") {
      running = false;
      std::cout << "...quitting\n";
    } else if (std::isdigit(in[0])) {
      scalars.push_back(std::stof(in));
      std::cout << "stored: " << scalars.at(scalars.size()-1) << std::endl;
    }else if(in == "list-scalars"){
      for(float f : scalars){
        std::cout << f << ", ";
      }
      std::cout << std::endl;
    } else {
      std::cout << "Nothing\n";
    }
  }
  return 0;
}
