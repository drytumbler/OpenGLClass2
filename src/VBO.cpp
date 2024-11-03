// VBO.cpp

#include "VBO.h"
#include <iostream>

VBO::VBO(const std::vector<float> data, const std::vector<VertexAttribute> layout)
  :attributes(layout), vertices(data){
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);

  if (ID == 0) {
    std::cout << "Failed to generate VBO" << std::endl;
  }
 
  
  glBufferData(GL_ARRAY_BUFFER,
	       vertices.size() * sizeof(float),
	       vertices.data(),
	       GL_STATIC_DRAW);
}



void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }


void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }


VBO::~VBO() { glDeleteBuffers(1, &ID); }


