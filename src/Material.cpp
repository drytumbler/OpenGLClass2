#include "Material.h"

Material::Material(const char *filename)
{
    //load the image (cpu)
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(
        filename, 
        &width, 
        &height, 
        &channels, 
        0 // STBI_rgb_alpha
    );
    
    // Determine the format of the image data
    GLenum format;
    if (channels == 1) {
        format = GL_RED;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    } else {
        std::cerr << "Unsupported number of channels: " << channels << std::endl;
        stbi_image_free(data);
    }

    //create texture (gpu)
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    #ifdef DEBUG_ENABLED
    std::cout << "Bound texture " << filename << " to ID #" << textureID << "." << std::endl;
    #endif
    //load image data (gpu)
    glTexImage2D(
        GL_TEXTURE_2D,      // target
        0,                  // mipmap level
        format,            // internal format
        width,
        height,
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

    State::GetInstance().Add(this);

}

Material::~Material()
{
    glDeleteTextures(1, &textureID);
}

void Material::Use()
{
  //glActiveTexture(GL_TEXTURE0 + index);
  glActiveTexture(GL_TEXTURE0 + (textureID - 1)); // TODO
  glBindTexture(GL_TEXTURE_2D, textureID);
}
