#include "Material.h"
#include "State.h"
Material::Material(const char *filename, const char type)
{
    //load the image (cpu)
    //int width, height, channels;
    Type = type;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(
        filename, 
        &Width, 
        &Height, 
        &Channels, 
        0 // STBI_rgb_alpha
    );
    
    // Determine the format of the image data
    GLenum format;
    if (Channels == 1) {
        format = GL_RED;
    } else if (Channels == 3) {
        format = GL_RGB;
    } else if (Channels == 4) {
        format = GL_RGBA;
    } else {
        std::cerr << "Unsupported number of channels: " << Channels << std::endl;
        stbi_image_free(data);
    }

    //create texture (gpu)
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //load image data (gpu)
    glTexImage2D(
        GL_TEXTURE_2D,      // target
        0,                  // mipmap level
        format,            // internal format
        Width,
        Height,
        0,                  // border
        format,            // format
        GL_UNSIGNED_BYTE,   // type
        data                // dahhh
    );

    //free data (cpu)
    stbi_image_free(data);

    //configure sampler wrapping S and T axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //configure sampler min and mag filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //    glGenerateMipmap(GL_TEXTURE_2D);
    glGenerateTextureMipmap(textureID);
    Path = filename;
    // TODO add intelligence
    getBaseName(Path, Uniform, 32);
    if (Type){
      Uniform[strlen(Uniform)] = type;
      Uniform[strlen(Uniform)+1] = '\0';
    } else {
      Uniform[strlen(Uniform)] = '\0';
    }
    
#ifdef DEBUG_ENABLED
    std::cout << "Bound texture " << filename << " to ID #" << textureID << "." << std::endl;
    std::cout << "Uniform: " << Uniform << std::endl;
#endif
}

Material::~Material()
{
    glDeleteTextures(1, &textureID);
#ifdef DEBUG_ENABLED
    std::cout << "Unound texture " << Path << " @ ID #" << textureID << "." << std::endl;
    //std::cout << "Uniform: " << Uniform << std::endl;
#endif
    /*
    int total = State::GetInstance().Materials.size();
    for(int i = 0; i <  total; i++){
      if (State::GetInstance().Materials[i]->textureID == textureID) State::GetInstance().Materials.erase(State::GetInstance().Materials.begin() + i);
    }
    */
}

void Material::Refresh(const char* filename) {
  // TODO copied code - make function ?
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(
        filename, 
        &Width, 
        &Height, 
        &Channels, 
        0 // STBI_rgb_alpha
    );
    
    // Determine the format of the image data
    GLenum format;
    if (Channels == 1) {
        format = GL_RED;
    } else if (Channels == 3) {
        format = GL_RGB;
    } else if (Channels == 4) {
        format = GL_RGBA;
    } else {
        std::cerr << "Unsupported number of channels: " << Channels << std::endl;
        stbi_image_free(data);
    }

    //refresh texture data (gpu)
    glBindTexture(GL_TEXTURE_2D, textureID);

    //load image data (gpu)
    glTexImage2D(
        GL_TEXTURE_2D,      // target
        0,                  // mipmap level
        format,            // internal format
        Width,
        Height,
        0,                  // border
        format,            // format
        GL_UNSIGNED_BYTE,   // type
        data                // dahhh
    );

    //free data (cpu)
    stbi_image_free(data);

    //configure sampler wrapping S and T axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //configure sampler min and mag filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //    glGenerateMipmap(GL_TEXTURE_2D);
    glGenerateTextureMipmap(textureID);
    Path = filename;
    getBaseName(Path, Uniform, 32);
    Uniform[strlen(Uniform)] = '\0';

#ifdef DEBUG_ENABLED
    std::cout << "Bound texture " << filename << " to ID #" << textureID << "." << std::endl;
    std::cout << "Uniform: " << Uniform << std::endl;
#endif
}

void Material::Use()
{
  //glActiveTexture(GL_TEXTURE0 + index);
  glActiveTexture(GL_TEXTURE0 + (textureID - 1)); 
  glBindTexture(GL_TEXTURE_2D, textureID);
}

void Material::Report() {
  std::cout << "Material " << textureID << " reporting.\n" << this << std::endl;
}
