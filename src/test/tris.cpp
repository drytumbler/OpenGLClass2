#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
struct Vertex {
  float x, y, z;  
};
int main() {
  const char* path = "../models/utahpot.tris";
  std::fstream myFile(path);
  std::vector<Vertex> vertices;
  for(std::string line; std::getline(myFile, line); ){
    float vertex[3];

    std::istringstream in(line);
    float x, y, z;
    if (in >> x >> y >> z){
      Vertex vertex;
      vertex.x = x;
      vertex.y = y;
      vertex.z = z;
      
      vertices.push_back(vertex);
    }  
  }
  for (auto vertex : vertices){
    std::cout << "{ " << vertex.x << ", " << vertex.y << ", " << vertex.z << " }" <<std::endl;
  }
  return 0;
}
