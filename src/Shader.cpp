// Shader.cpp

#include "Shader.h"

unsigned int makeShaderMod(const std::string& filepath, unsigned int shader_type){
    
    // load the shader code (cpu)
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)){
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    //load and compile the shader module (gpu)
    unsigned int shaderModule = glCreateShader(shader_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    //error handling
    int succes;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &succes);
    if(succes == GL_FALSE){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module Compilation Error in " << ((shader_type == 0x8B30 ) ? "fragment":"vertex" )<< ":\n" <<errorLog << std::endl;
	glDeleteShader(shaderModule);
        return 0;
    }

    return shaderModule;
}

Shader::Shader(const std::string &vertex_filepath,
               const std::string &fragment_filepath)
  : vertexPath(vertex_filepath), fragmentPath(fragment_filepath) {
    std::vector<unsigned int> modules;
    modules.push_back(makeShaderMod(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(makeShaderMod(fragment_filepath, GL_FRAGMENT_SHADER));

    ID = glCreateProgram();
    for (unsigned int shaderModule : modules){
        glAttachShader(ID, shaderModule);
    }
    glLinkProgram(ID);

    //error handling
    int succes;
    glGetProgramiv(ID, GL_LINK_STATUS, &succes);
    if(succes == GL_FALSE){
        char errorLog[1024];
        glGetProgramInfoLog(ID, 1024, NULL, errorLog);
        std::cout << "Shader Program Linking Error:\n" <<errorLog << std::endl;
    }
    //clean up
    for (unsigned int shaderModule : modules){
        glDeleteShader(shaderModule);
    }
}

void Shader::Activate() { glUseProgram(ID); }

void Shader::Delete() { glDeleteShader(ID); }

// other error checking function...
void Shader::CompileErrors(unsigned int shader, const char *type) {
  GLint succes;
  char infoLog[1024];
  if (type != "PROGRAM"){
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
    if (succes == GL_FALSE){
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "Shader compilation error for: " << type << "\n" << std::endl;
    }
  }
  else {
    if (succes == GL_FALSE){
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "Shader linking error for: " << type << "\n" << std::endl;
    }
  }
}


void Shader::Refresh(GLFWwindow* window) {

  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

    glDeleteShader(ID);
    
    std::cout << "refreshing.." << std::endl;

    std::vector<unsigned int> modules;
    modules.push_back(makeShaderMod(vertexPath, GL_VERTEX_SHADER));
    modules.push_back(makeShaderMod(fragmentPath, GL_FRAGMENT_SHADER));

    ID = glCreateProgram();
    for (unsigned int shaderModule : modules){
      glAttachShader(ID, shaderModule);
    }
    glLinkProgram(ID);
    
    //error handling
    int succes;
    glGetProgramiv(ID, GL_LINK_STATUS, &succes);
    if(succes == GL_FALSE){
      char errorLog[1024];
      glGetProgramInfoLog(ID, 1024, NULL, errorLog);
      std::cout << "Shader Program Linking Error:\n" <<errorLog << std::endl;
    }
    //clean up
    for (unsigned int shaderModule : modules){
      glDeleteShader(shaderModule);
    }

    glUseProgram(ID);
  }
}
