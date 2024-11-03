// TriangleMesh.h
#pragma once

#include <iomanip>

#include "config.h"
#include "IBO.h"
#include "VBO.h"
#include "VAO.h"

class TriangleMesh {
public:
  TriangleMesh(std::vector<VBO*>& vbos, IBO* ibop);
  void draw();
  void Report();
  ~TriangleMesh();

private:
  IBO* ibo;
  std::vector<VBO*> VBOs;
  VAO* vao;
  unsigned int vertex_count;
};
