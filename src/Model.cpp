// Model.cpp

#include "Model.h"

std::vector<float> import_tris(const char* filename);

Model::Model(const std::string& filename) :Path(filename) {
  unsigned int filter = extension_filter(filename); 
  if (!FILTER_MODEL(filter)) {
    printf("file denied: not a Model file\n%s\n", filename.c_str());
    return;
  }
  if (FILTER_TRIS(filter)){
    std::vector<float> vertices = import_tris(filename.c_str());
    std::vector<VertexAttribute> attributes = {
      VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0, false),
    };
    VBOp = new VBO(vertices, attributes);
    printf("tris model created: %s\n", filename.c_str());
  }
  
}

Model::~Model() {
  delete VBOp;
  printf("model closed: %s\n", Path.c_str());
}

void Model::Draw(Shader& shader, Camera& camera) {
  for(auto& vbo : VBOs){
    vbo->Bind();
  }
  vao->Bind();
  ibo->Bind();
    //glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}


std::vector<float> import_tris(const char* filename) {
  std::fstream myFile(filename);
  std::vector<float> vertices;
  for(std::string line; std::getline(myFile, line); ){
    std::istringstream in(line);
    float x, y, z;
    if (in >> x >> y >> z){
      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
    }  
  }
  return vertices;
}
