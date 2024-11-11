#pragma once
#include <iostream>
#include <vector>

class VBO;
class TriangleMesh;
class Material;

class State { // Singleton structure
public:
  std::vector<VBO*> VBOs;
  std::vector<TriangleMesh*> Meshes;
  std::vector<Material*> Materials;

  static State& GetInstance(){
    static State instance;
    return instance;
  }
  void Add(VBO* vbo){ VBOs.push_back(vbo); puts("VBO registered"); }
  void Add(TriangleMesh* mesh){ Meshes.push_back(mesh); puts("Mesh registered"); }
  void Add(Material* material){ Materials.push_back(material); puts("Material registered"); }

private:
  State() = default;
  State(const State&) = delete;
  State& operator=(const State&) = delete;
};
