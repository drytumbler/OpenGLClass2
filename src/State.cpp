// State.cpp

#include "State.h"

void State::Report(){
  for(auto& m : Materials) {
    m->Report();
  }
  for(VBO* v : VBOs) {
    v->Report();
  }
  for(TriangleMesh* t : Meshes) {
    t->Report();
  }
  for(Shader* s : Shaders){
    s->Report();
  }
}

void State::LoadTextures() {
  if(TexturesLoaded) return;
  std::filesystem::path dir{expandHome(TEXTURES)};
  std::vector<std::filesystem::path> dirs;
  std::vector<std::filesystem::path> files;
  
  for(auto const& dir_entry : std::filesystem::directory_iterator{dir}){
    if(dir_entry.is_directory())
      dirs.push_back(dir_entry);
    else if(dir_entry.is_regular_file())
      files.push_back(dir_entry);
  }
  
  for (const auto& path : files){
    Materials.push_back(new Material(path.c_str()));
  }
  for (Material* material : Materials){
    printf("Material registered as %s\n", material->GetUniform());
  }
  printf("Materials count: %lu\n", Materials.size());
  TexturesLoaded = true;
}
