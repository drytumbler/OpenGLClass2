// TriangleMesh.cpp

#include "TriangleMesh.h"
#include "Camera.h"
#include "State.h"

TriangleMesh::TriangleMesh(std::vector<VBO*>& vbos, IBO*& ibop, std::vector<Material*> texp) : VBOs(vbos), ibo(ibop), TEXs(texp){
  ID = State::GetInstance().Meshes.size();
  vao = new VAO();
  vao->Bind();

  // Create VAO and add VBOs
  for(auto& vbo : vbos){
    vbo->Bind();
    for(auto& attr : vbo->attributes){
      vao->LinkAttrib(*vbo, attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.offset);
    }
    vbo->Unbind();
  }
  vao->Unbind();
  vertex_count = ibo->indices.size();

  State::GetInstance().Add(this);
}

void TriangleMesh::Draw(Shader& shader, Camera& camera) {
  for(auto& vbo : VBOs){
    vbo->Bind();
  }
  vao->Bind();
  ibo->Bind();
    //glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
  glDeleteVertexArrays(1, &vao->ID);
  glDeleteBuffers(1, &ibo->ID);

  int total = State::GetInstance().Meshes.size();
  for(int i = 0; i <  total; i++){
    if (State::GetInstance().Meshes[i]->ID == ID) State::GetInstance().Meshes.erase(State::GetInstance().Meshes.begin() + i);
  }
  
  delete vao; 
}

//--------------------------
#ifdef DEBUG_ENABLED
//--------------------------

void TriangleMesh::Report() {
  std::cout << "TriangleMesh reporting: OK @ " << this << std::endl;
  std::cout << "data received:" << std::endl;
  for (auto& vbo : VBOs){
    std::cout << "VBO " << vbo->ID << ": " << vbo << std::endl;
    vbo->Bind();
    std::vector<float> readBackVertices(vbo->vertices.size());
    //glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, vbo->vertices.size() * sizeof(float), readBackVertices.data());

    // Print read back vertices
    std::cout << "Read back vertices from VBO:" << std::endl;
    int inc;
    //inc = vbo->attributes[0].size;
    int loop = 0;
    int index = 0;
    int num_attr = vbo->attributes.size();
    std::cout << "readBackvertices.size() = " << readBackVertices.size() << ".\n" << std::endl;
    for (size_t i = 0; i < readBackVertices.size(); i += inc) {
      loop = loop % num_attr;
      inc = vbo->attributes[loop++].size;
      if (loop == 1) {
	std::cout << "#" << index++ << " - ";
      }
      if (inc == 3){
	std::cout << std::fixed << std::setprecision(3) << "("
		  << readBackVertices[i] << ", "
		  << readBackVertices[i + 1] << ", "
		  << readBackVertices[i + 2] << ")\t ";
      }
      else if (inc == 2) {
	std::cout << std::fixed << std::setprecision(3)<< "("
		  << readBackVertices[i] << ", "
		  << readBackVertices[i + 1] << ")\t ";
      }
      else if (inc == 1) {
	std::cout << std::fixed << std::setprecision(3)<< "("
		  << readBackVertices[i] << ")\t ";
      }
      if (loop == num_attr) {
	std::cout << std::endl;
      }
    }
    
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbo->Unbind();			     
  }
  

  std::vector<int> readBackIndices(ibo->indices.size());
  ibo->Bind();
  glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, ibo->indices.size() * sizeof(int), readBackIndices.data());
  // Print read back indices
  std::cout << "IBO " << ibo->ID << ": " << ibo << std::endl;
  std::cout << "Read back indices from IBO:" << std::endl;
  for (size_t i = 0; i < readBackIndices.size(); i += 3) {
    std::cout << "("
	      << readBackIndices[i] << ", "
	      << readBackIndices[i + 1] << ", "
	      << readBackIndices[i + 2] << ")" << std::endl;
  }
  ibo->Unbind();
}

//--------------------------
#endif
//--------------------------
