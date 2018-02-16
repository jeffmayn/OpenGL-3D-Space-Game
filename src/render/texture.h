//
// Created by chris on 05.12.2017.
//

#ifndef LEARN_OPENGL_TEXTURE_H
#define LEARN_OPENGL_TEXTURE_H

#include <iostream>
#include <string>

#include "../../include/glad/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/stb/stb_image.h"

void loadTextures(GLuint* texture, const char* filePath, GLenum param1, GLenum param2, GLuint alphaEnabled);
#endif //LEARN_OPENGL_TEXTURE_H
