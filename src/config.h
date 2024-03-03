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

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void setupGLFW();
GLFWwindow *createWindow();
unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type);
unsigned int makeShaderProg(const std::string& vertex_filepath, const std::string& fragment_filepath);

// Window dimensions
const GLuint WIDTH = 600, HEIGHT = 600;

//constants
#define PI 3.14159627
