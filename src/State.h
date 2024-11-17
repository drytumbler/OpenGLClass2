// State.h
#pragma once

#define TEXTURES "../src/textures"
#define MESHES "../src/models"
#define SHADERS "../src/shaders"

#include <iostream>
#include <vector>
//#include "Material.h"
//class VBO;
//class TriangleMesh;
//class Material;
#include "VBO.h"
#include "TriangleMesh.h"
class State { // Singleton structure
public:
  std::vector<VBO*> VBOs;
  std::vector<TriangleMesh*> Meshes;
  std::vector<Material*> Materials;
  std::vector<Shader*> Shaders;

  static State& GetInstance(){
    static State instance;
    return instance;
  }
  void Add(VBO* vbo){ VBOs.push_back(vbo); puts("VBO registered"); }
  void Add(TriangleMesh* mesh){ Meshes.push_back(mesh); puts("Mesh registered"); }
  void Add(Shader* shader){ Shaders.push_back(shader); puts("Shader registered"); }
  void Report();

  void Add(Material* material){
    printf("Material registered as %s\n", material->GetUniform());
    Materials.push_back(std::move(material));
    printf("Materials: %lu\n", Materials.size());
  }

  void LoadTextures();
  bool GetTexturesLoaded() { return TexturesLoaded; }

  void RemoveAllMaterials() { Materials.clear(); printf("Materials: %lu\n", Materials.size()); }
private:
  State() = default;
  State(const State&) = delete;
  State& operator=(const State&) = delete;
  bool TexturesLoaded = false;
};
