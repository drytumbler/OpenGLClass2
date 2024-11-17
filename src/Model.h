// Model.h
#include "config.h"
#include "VAO.h"
#include "Shader.h"
#include "Camera.h"
#include <filesystem>

class Model {

 public:
  Model(const std::string& filename);
  ~Model();

  void Draw(Shader& shader, Camera& camera);
  
 private:
  std::filesystem::path Path;
  VBO* VBOp;
  VAO* VAOp;
  unsigned int vertex_count;
  
};
