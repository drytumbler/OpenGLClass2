// Sphere.cpp

#include "Sphere.h"

Sphere::Sphere(float size, int depth) {
  vertices.push_back(glm::vec3(0.0f, size, 0.0f));
  for(int i = 0; i < depth; i++){
    float height = abs(size - size / depth * (i + 1));
    float radius = sqrt(size * size - height * height);
    for(int j = 0; j < depth; j++){
      float inc = 2 * PI / depth;
      float xC = cos(j * inc) * radius;
      float zC = sin(j * inc) * radius;
      vertices.push_back(glm::vec3(xC, height, zC));
      
    }
  }
  vertices.push_back(glm::vec3(0.0f, -size, 0.0f));
}

void Sphere::Report() {
  for(auto vector : vertices){
    std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
  }
}


int main() {
  Sphere C(15, 8);
  C.Report();
  return 0;
}
