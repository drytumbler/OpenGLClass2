// Camera.h

#pragma once

#include "config.h"
#include "Shader.h"

class Camera {
 public:
  glm::vec3 keyVector = glm::vec3(1.0, 1.0, 1.0);
  glm::vec3 mouseVector = glm::vec3(1.0, 1.0, 1.0);
  glm::vec3 position;
  glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
  
  glm::mat4 cameraMatrix = glm::mat4(1.0f);

  bool firstClick = true;
  
  int width, height;
  
  float speed = .1f;
  float sensitivity = 100.0f;

  Camera(int width, int height, glm::vec3 center);

  void Update(float FOV, float near, float far);
  void Inputs(GLFWwindow* window);
  void Export(Shader& shader, const char* uniform);
  void ExportPos(Shader& shader, const char* uniform);
  void ExportDir(Shader& shader, const char* uniform);
  void ExportRight(Shader& shader, const char* uniform);
  void setKeyVector(glm::vec3 vec);
  void setMouseVector(glm::vec3 vec); 
};
