// Primitive.cpp

#include "Primitive.h"

// FIXME: type also needs to be passed to shader, maybe as static array that keeps track of all primitives?

Primitive::Primitive(glm::vec3 position, GLfloat size, std::string type) : position(position), size(size){
  
}

void Primitive::Export(Shader &shader, const char *uniform) { 
  glm::vec4 data = glm::vec4(position, size);
  glUniform4fv(glGetUniformLocation(shader.ID, uniform), 1, glm::value_ptr(data)); 
}
