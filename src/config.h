#pragma once
// GLAD
#include "../include/glad/glad.h"
// GLFW (include after glad)
#include <GLFW/glfw3.h>

// other includes
#include <iostream> //console io
#include <string>   //work with strings
#include <fstream>  //open files
#include <sstream>  //stream files into strings

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void setupGLFW();
GLFWwindow *createWindow();
unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type);
unsigned int makeShaderProg(const std::string& vertex_filepath, const std::string& fragment_filepath);
void saveScreenshotToFile(std::string filename, int windowWidth, int windowHeight);
// Window dimensions
const GLuint WIDTH = 1200, HEIGHT = 900;

//constants
#define PI (float)3.14159627

// macros
#define abs(X) ((X<0)?-X:X)
