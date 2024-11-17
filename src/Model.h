// Model.h
#include "config.h"
#include "VAO.h"
#include <filesystem>

class Model {

 public:
  Model(const std::string& filename);
  ~Model();

  void Draw();
  
 private:
  std::filesystem::path Path;
  VBO* VBOp;
  VAO* VAOp;
  
};
