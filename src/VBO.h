// VBO.h

#pragma once

#include "../include/glad/glad.h"
#include <vector>
#include <iostream>



class VertexAttribute {
public:
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  void* offset;
  bool isInt;

  VertexAttribute(GLuint idx, GLint sz, GLenum tp, GLboolean norm, GLsizei str, void* off, bool intType = false)
        : index(idx), size(sz), type(tp), normalized(norm), stride(str), offset(off), isInt(intType) {  }
};

class VBO {
public:
  GLuint ID;
  std::vector<float> vertices;
  VBO(const std::vector<float> data);
  void Bind();
  void Unbind();
  void Report();
  ~VBO();
};


