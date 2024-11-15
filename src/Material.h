#pragma once

#include "config.h"
#include "../include/stb_image.h"
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

class Material{
public:
  bool Active = false;
  Material(const char* filename, const char type = 0);
  ~Material();
  void Use();
  void Report();
  void Refresh(const char* filename);
  GLuint GetID(){ return textureID; }
  const char* GetUniform(){ return Uniform; }
private:
  GLuint textureID;
  int Width, Height, Channels;
  std::string Path;
  char Uniform[32];
  char Type;
};
