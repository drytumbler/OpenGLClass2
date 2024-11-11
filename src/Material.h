#pragma once

#include "config.h"
#include "../include/stb_image.h"
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "State.h"

class Material{
    public:
        Material(const char* filename);
        ~Material();
        void Use();
    private:
    GLuint textureID;
};
