// Model.cpp

#include "Model.h"
struct TrisModel {
  std::vector<float> Vertices;
  unsigned int vertex_count = 0;
};

TrisModel import_tris(const char* filename);

Model::Model(const std::string& filename) :Path(filename) {
  unsigned int filter = extension_filter(filename); 
  if (!FILTER_MODEL(filter)) {
    printf("file denied: not a Model file\n%s\n", filename.c_str());
    return;
  }
  if (FILTER_TRIS(filter)){
    TrisModel model  = import_tris(filename.c_str());
    const std::vector<VertexAttribute> attributes = {
      VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0, false),
    };
    VBOp = new VBO(model.Vertices);
    VAOp = new VAO(*VBOp, attributes);
    vertex_count = model.vertex_count;
    printf("tris model created: %s\n %d vertices.\n", filename.c_str(), vertex_count);
  }
}

Model::~Model() {
  delete VBOp;
  delete VAOp;
  printf("model closed: %s\n", Path.c_str());
}

void Model::Draw(Shader& shader, Camera& camera) {
  VBOp->Bind();
  VAOp->Bind();
  //ibo->Bind();
  glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  //glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}


TrisModel import_tris(const char* filename) {
  std::fstream myFile(filename);
  TrisModel model;
  for(std::string line; std::getline(myFile, line); ){
    if(line == "" || line =="\n" || isInteger(line)) continue;
    std::istringstream in(line);
    float x, y, z;
    if (in >> x >> y >> z){
      model.Vertices.push_back(x);
      model.Vertices.push_back(y);
      model.Vertices.push_back(z);
    }  
    model.vertex_count++;
  }
  return model;
}
