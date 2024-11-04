// TriangleMesh.cpp

#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(std::vector<VBO*>& vbos, IBO* ibop) : VBOs(vbos), ibo(ibop){
    
  vao = new VAO();

  // Create and add VBOs

  for(auto& vbo : vbos){
    vbo->Bind();
    for(auto& attr : vbo->attributes){
      vao->LinkAttrib(*vbo, attr.index, attr.size, attr.type, attr.normalized, attr.stride, attr.offset);
    }
    vbo->Unbind();
  }
 
    vertex_count = ibo->size;

    //no attributes to set here..

}

void TriangleMesh::draw() {
  for(auto& vbo : VBOs){
    vbo->Bind();
  }
  vao->Bind();
  ibo->Bind();
    //glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

void TriangleMesh::Report() {
  std::cout << "data received:" << std::endl;
  for (auto& vbo : VBOs){
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

  std::vector<int> readBackIndices(ibo->size);
  ibo->Bind();
  glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, ibo->size * sizeof(int), readBackIndices.data());
  // Print read back indices
  std::cout << "Read back indices from IBO:" << std::endl;
  for (size_t i = 0; i < readBackIndices.size(); i += 3) {
    std::cout << "("
	      << readBackIndices[i] << ", "
	      << readBackIndices[i + 1] << ", "
	      << readBackIndices[i + 2] << ")" << std::endl;
  }
  ibo->Unbind();
	
}

TriangleMesh::~TriangleMesh() {
  glDeleteVertexArrays(1, &vao->ID);
  glDeleteBuffers(1, &ibo->ID);

  delete vao;
  delete ibo;
  
}
