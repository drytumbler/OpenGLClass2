#pragma once

//#include "Material.h"
//#include "TriangleMesh.h"
#define DEBUG_ENABLED
#define UI_ENABLED
// #undef UI_ENABLED

#ifndef DEFAULT_SAVE_PATH
#define DEFAULT_SAVE_PATH (expandHome("~/projects/OpenGLClass2/src/shaders"))
#endif

#ifndef DEFAULT_LOAD_PATH
#define DEFAULT_LOAD_PATH (expandHome("~/projects/OpenGLClass2/src/shaders"))
#endif

// GLAD
#include "glad/glad.h"
// GLFW (include after glad)
#include <GLFW/glfw3.h>

// other includes
#include <iostream> //console io
#include <string>   //work with strings
#include <fstream>  //open files
#include <sstream>  //stream files into strings
#include <filesystem>
#include <vector>

#include "nfd/nfd.h"


#define GLM_ENABLE_EXPERIMENTAL //for bending spacetime

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard window dimensions
//const GLuint WIDTH = 400, HEIGHT = 300;
//constants

#ifndef WIDTH
#define WIDTH 500
#endif
#ifndef HEIGHT
#define HEIGHT 500
#endif

#define PI (float)3.14159627f

#define RECENT_DOCS_FILE "recent.ini"
#define MAX_RECENT_DOCUMENTS 10

int checkAndCreateFile(const std::string& filename);
void appendToFile(const std::string &filename, const char *text);
int saveToFile(const std::string& filePath, const char* data); 
void appendToRecentDocuments(const char *text);
std::filesystem::path constructFullPath(const char *path, const char *name);
std::uintmax_t getFileSize(const std::string& filePath);
std::string expandHome(const std::string& path);
