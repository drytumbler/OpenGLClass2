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
  TriangleMesh(VBO* vbo, std::vector<VertexAttribute> attributes, IBO* ibo = nullptr);
  ~TriangleMesh();
  void Draw(Shader& shader, Camera& camera);

#ifdef DEBUG_ENABLED
  void Report();
#endif

private:
  int ID;
  VBO* vbo;
  IBO* ibo;
  VAO* vao;

  std::vector<VertexAttribute> Attributes;
  unsigned int vertex_count;
};
