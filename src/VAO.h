// VAO.h

#pragma once

#include "../include/glad/glad.h"
#include "VBO.h"

class VAO {
 public:
  GLuint ID;
  VAO();

  void LinkAttrib(const VBO& VBO, GLuint layout, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, void* offset);
  void Bind();
  void Unbind();
  void Delete();
};
