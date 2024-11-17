// config.cpp
#include "config.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <sys/stat.h>
#include <unistd.h>

int checkAndCreateFile(const std::string& filename) {
    std::ifstream file(filename);  // Attempt to open the file
    if (!file) {  // If file does not exist
        std::ofstream newFile(filename);  // Create the file
        if (newFile) {
            std::cout << "File created: " << filename << std::endl;
	    return 0;
        } else {
            std::cerr << "Failed to create file: " << filename << std::endl;
	    return -1;
        }
    } else {
        std::cout << "File exists: " << filename << std::endl;
	return 1;
    }
    return -1;
}

void appendToFile(const std::string& filename, const char* text) {
    std::ofstream file(filename, std::ios::app);  // Open in append mode
    if (file) {
        file << text;  // Append the text
        std::cout << "Appended to file: " << filename << std::endl;
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

int saveToFile(const std::string& filePath, const char* data) {
    std::ofstream file(filePath, std::ios::out | std::ios::trunc);  // Open file in overwrite mode
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return -1;
    }

    file << data;  // Write data to the file, overwriting existing content
    file.close();
    return 0;
}


std::filesystem::path constructFullPath(const char *path, const char *name) {
  std::string combine = path;
  combine += name;
  std::filesystem::path fullpath = combine.c_str();
  return fullpath;
}

const char* getBaseName(std::filesystem::path path, char* basename, int size){
    int n = strlen(path.filename().c_str()) - strlen(path.extension().c_str());
    strncpy(basename, path.filename().c_str(), n);
    basename[(int)fmin(n, size-1)] = '\0';
    return basename;
}

std::uintmax_t getFileSize(const std::string& filePath) {
    try {
        return std::filesystem::file_size(filePath);  // Returns file size in bytes
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
}

std::string expandHome(const std::string& path) {
    if (path[0] == '~') {
        const char* home = getenv("HOME"); // Unix-like systems
        if (!home) home = getenv("USERPROFILE"); // Windows fallback
        if (home) {
            return std::string(home) + path.substr(1);
        }
    }
    return path; // return original if no expansion
}

std::string get_file_string(const char* filepath){
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)){
        bufferedLines << line << "\n";
    }
    std::string result = bufferedLines.str();

    bufferedLines.str("");
    file.close();

    return result;
}

inline bool exists (const std::string& name) {
  //std::filesystem::exists(name); // alternative
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}

unsigned int extension_filter(std::filesystem::path path) {
  unsigned int  result = 0x00;
  if ( !exists(path) ){
    printf("path not found: %s\n", path.c_str());
    return 0xFF;
  }

  if( ((std::filesystem::directory_entry)path).is_directory() )
    return result; // 0x00 = directory
    
  if( path.has_extension() ){
    const std::string extension  = path.extension().c_str();
    const char* filters[3][4] = {   // always fill array, empty strings are ignored   
      {".frag", ".vert", ".glsl", ".shader"},
      {".png", ".jpg", ".bmp", ""},
      {".obj", ".step", ".tris", ""},
    };
    for(int i = 0; i < sizeof(filters) / sizeof(filters[0]); i++){ // rows
      for(int j = 0; j < sizeof(filters[0]) / sizeof(filters[0][0]); j++){ // columns
	if( strcmp(filters[i][j], extension.c_str()) == 0 ) {
	                                 // 00000000 00000000 00000000 00000000 00000000 00000000 result
	  result |= j + 1;               // 00000001 00000010 00000001 00000010 00000001 00000010 j
	  result |= ((i + 1) << 4);      // 00010000 00010000 00100000 00100000 00110000 00110000 i
	  return result;                 // ----------------------------------------------------- +
	}                                // 00010001 00010010 00100001 00100010 00110001 00110010
      }	                                 //     0x11     0x12     0x21     0x22     0x31     0x32
    }                                    //    .frag    .vert     .png     .jpg     .obj    .step  
                                         //       if the path has an extension: 1 < result < 0xFF
  }                                      //     if the path slipped the filter the result still 0
  
  
    return  0xFF;  // return the result or 0xFF if the file has no extension or unknown extension
}

bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}
