// Shader.h

#pragma once

// #include "config.h"
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
// #include <glm/glm.hpp>

unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type);

class Shader {
public:
  GLuint ID;
  Shader(const std::string &vertex_filepath, const std::string &fragment_filepath);
  void Activate();
  void Delete();
  void Refresh(GLFWwindow* window);

private:
  std::string vertexPath;
  std::string fragmentPath;
  
  void CompileErrors(unsigned int shader, const char* type);
};
