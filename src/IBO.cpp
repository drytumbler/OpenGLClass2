// IBO.cpp

#include "IBO.h"

IBO::IBO(const std::vector<GLuint> data) : indices(data) {

  glGenBuffers(1, &ID);

  if (ID == 0) {
    std::cout << "Failed to generate IBO" << std::endl;
  }
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	       indices.size() * sizeof(unsigned int),
	       indices.data(),
	       GL_STATIC_DRAW);
}

void IBO::Delete() { glDeleteBuffers(1, &ID); }


void IBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }


void IBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
