#pragma once
#include "config.h"
#include "IBO.h"
#include "VBO.h"
#include "VAO.h"

class Sphere {
 public:
  float radius;
  std::vector<glm::vec3> vertices;
  Sphere(float size, int depth);
  void Draw();
  void Report();

 private:
  IBO* ibo;
  std::vector<VBO*> VBOs;
  VAO* vao;
  unsigned int vertex_count;
};
