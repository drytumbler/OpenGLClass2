// Shader.h

#pragma once

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type);

class Shader {
public:
  bool Active = false;
  GLuint ID;
  Shader(const std::string &vertex_filepath, const std::string &fragment_filepath);
  Shader(const char* vertData, const char* fragData, bool rawFlag);
  Shader();
  void Activate();
  void Delete();
  void Refresh();
  void Report() { std::cout <<( (this == &StaticShader) ? "StaticShader " : "Shader" ) << ID << " reporting!" << std::endl; }

  std::string GetVertexShaderPath();
  std::string GetFragmentShaderPath();

  void SetVertexShaderPath(const char * filepath);
  void SetFragmentShaderPath(const char* filepath);

  static Shader StaticShader;
  static Shader pushShader(const char* vertData, const char* fragData);

private:
  
  std::string vertexPath;
  std::string fragmentPath;
  
  void CompileErrors(unsigned int shader, const char* type);
  static void SetStaticShader(Shader shader){ StaticShader = shader; } 
};
