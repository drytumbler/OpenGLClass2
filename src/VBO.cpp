// VBO.cpp

#include "VBO.h"
#include "State.h"

VBO::VBO(const std::vector<float> data)
  : vertices(data){
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);

  if (ID == 0) {
    std::cout << "Failed to generate VBO" << std::endl;
  }
 
  
  glBufferData(GL_ARRAY_BUFFER,
	       vertices.size() * sizeof(float),
	       vertices.data(),
	       GL_STATIC_DRAW);
  
  State::GetInstance().Add(this);
}



void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, ID); }


void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Report(){   std::cout << "VBO " << ID << " reporting.\n" << this << std::endl;}

VBO::~VBO() {
  glDeleteBuffers(1, &ID);
  int total = State::GetInstance().VBOs.size();
  for(int i = 0; i <  total; i++){
    if (State::GetInstance().VBOs[i]->ID == ID) State::GetInstance().VBOs.erase(State::GetInstance().VBOs.begin() + i);
  }
}


