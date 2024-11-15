// TriangleMesh.h
#pragma once

//#define DEBUG_ENABLED //to be removed later

#include "config.h"

#include <iomanip>

#include "IBO.h"
//#include "VBO.h"
#include "VAO.h"
#include "Material.h"
#include "Camera.h"

class TriangleMesh {
public:
  TriangleMesh(std::vector<VBO*>& vbos, IBO*& ibop, std::vector<Material*> texp);
  ~TriangleMesh();

  void Draw(Shader& shader, Camera& camera);

#ifdef DEBUG_ENABLED
  void Report();
#endif

private:
  int ID;
  std::vector<VBO*> VBOs;
  IBO* ibo;
  std::vector<Material*> TEXs;

  VAO* vao;
  unsigned int vertex_count;
};
