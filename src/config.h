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

#define MAINX (.77)
#define SIDEX (1. - MAINX)

// FILTERS: filter array is define in extension_filter() in config.cpp. Could be a struct...
/*    {".frag", ".vert", ".glsl", ".shader"},
      {".png", ".jpg", ".bmp", ""},
      {".obj", ".step", ".tris", ""},*/

#define FILTER_SHADER(x)	( ((x) >= 0x11) && ((x) < 0x20) )
#define FILTER_TEXTURE(x)   	( ((x) >= 0x21) && ((x) < 0x30) )
#define FILTER_MODEL(x) 	( ((x) >= 0x31) && ((x) < 0x40) )

#define FILTER_TRIS(x)      	(  (x) == 0x33  )
#define FILTER_STEP(x)      	(  (x) == 0x32  )
#define FILTER_OBJ(x)       	(  (x) == 0x31  )

#define FILTER_BMP(x)       	(  (x) == 0x23  )
#define FILTER_JPG(x)       	(  (x) == 0x22  )
#define FILTER_PNG(x)       	(  (x) == 0x21  )

#define FILTER_FRAG(x)       	(  (x) == 0x11  )
#define FILTER_VERT(x)       	(  (x) == 0x12  )


int checkAndCreateFile(const std::string& filename);
void appendToFile(const std::string &filename, const char *text);
int saveToFile(const std::string& filePath, const char* data); 
void appendToRecentDocuments(const char *text);
std::filesystem::path constructFullPath(const char *path, const char *name);
std::uintmax_t getFileSize(const std::string& filePath);
std::string expandHome(const std::string& path);
const char* getBaseName(std::filesystem::path path, char* basename, int size);
std::string get_file_string(const char* filepath);
unsigned int extension_filter(std::filesystem::path file);
bool isInteger(const std::string & s);
