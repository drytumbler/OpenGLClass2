// IBO.h

#pragma once

#include "../include/glad/glad.h"
#include <iostream>
#include <vector>

class IBO {
 public:
  GLuint ID;
  std::vector<GLuint> indices;
  GLsizeiptr size;
  IBO(const std::vector<GLuint> data, const unsigned int amount);

  void Bind();
  void Unbind();
  void Delete();
};

