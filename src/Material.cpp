#include "Material.h"
#include <stb/stb_image.h>

Material::Material(const char *filename)
{
    //load the image (cpu)
    int width, height, channels;

    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(
        filename, 
        &width, 
        &height, 
        &channels, 
        STBI_rgb_alpha
    );

    //create texture (gpu)
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //load image data (gpu)
    glTexImage2D(
        GL_TEXTURE_2D,      // target
        0,                  // mipmap level
        GL_RGBA,            // internal format
        width,
        height,
        0,                  // border
        GL_RGBA,            // format
        GL_UNSIGNED_BYTE,   // type
        data                
    );

    //free data (cpu)
    stbi_image_free(data);

    //configure sampler wrapping S and T axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //configure sampler min and mag filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

Material::~Material()
{
    glDeleteTextures(1, &texture);
}

void Material::use(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture);
}
