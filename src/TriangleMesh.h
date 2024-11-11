// TriangleMesh.h
#pragma once

//#define DEBUG_ENABLED //to be removed later

#include "config.h"

#include <iomanip>

#include "IBO.h"
#include "VBO.h"
#include "VAO.h"
#include "Material.h"
#include "Camera.h"


class TriangleMesh {
public:
  TriangleMesh(std::vector<VBO*>& vbos, IBO* ibop);
  void Draw();
  #ifdef DEBUG_ENABLED
  void Report();
  #endif
  ~TriangleMesh();

private:
  IBO* ibo;
  std::vector<VBO*> VBOs;
  std::vector<Material*> TEXs;
  VAO* vao;
  unsigned int vertex_count;
};
