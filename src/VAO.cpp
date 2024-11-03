// VAO.cpp

#include "VAO.h"

VAO::VAO() {
  glGenVertexArrays(1, &ID);

  if (ID == 0) {
    std::cout << "Failed to generate VAO" << std::endl;
  }
  
  glBindVertexArray(ID);
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
