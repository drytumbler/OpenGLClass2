// Primitive.h

#pragma once

#include "config.h"
#include "Shader.h"

class Primitive {
 public:
  Primitive(glm::vec3 position, GLfloat size, std::string type);
  glm::vec3 position;
  GLfloat size;
  GLuint type;
  void Export(Shader& shader, const char* uniform);
};
