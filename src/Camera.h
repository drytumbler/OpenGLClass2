// Camera.h

#pragma once

#include "config.h"
#include "Shader.h"

class Camera {
 public:
  glm::vec3 position;
  glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  
  glm::mat4 cameraMatrix = glm::mat4(1.0f);

  bool firstClick = true;
  
  int width, height;
  
  float speed = .1f;
  float sensitivity = 100.0f;

  Camera(int width, int height, glm::vec3 center);

  void Update(float FOV, float near, float far);
  void Inputs(GLFWwindow* window);
  void Export(Shader& shader, const char* uniform);
};
