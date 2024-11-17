// VAO.cpp

#include "VAO.h"

VAO::VAO(VBO& VBOr, std::vector<VertexAttribute> attributes) {
  glGenVertexArrays(1, &ID);

  if (ID == 0) {
    std::cout << "Failed to generate VAO" << std::endl;
  }  
  glBindVertexArray(ID);
  VBOr.Bind();
  for(auto attr : attributes){
    LinkAttrib(VBOr, attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.offset);
  }
  VBOr.Unbind();
}

void VAO::LinkAttrib(const VBO& VBO, GLuint layout, GLuint size, GLenum type, GLboolean normalized, GLsizeiptr stride, void* offset){
  //VBO.Bind();
  glVertexAttribPointer(layout,
			size,
			type,
			normalized,
			stride,
			offset);
  glEnableVertexAttribArray(layout);
  //VBO.Unbind();
}

void VAO::Bind() { glBindVertexArray(ID); }
void VAO::Unbind() { glBindVertexArray(0); }
void VAO::Delete(){ glDeleteVertexArrays(1, &ID);}
