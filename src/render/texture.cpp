//
// Created by chris on 05.12.2017.
//

#include "texture.h"

GLint width, height, nrChannels;
/* Pointer to the memory address of where we store our loaded texture */
unsigned char *data;

void loadTextures(GLuint* texture, const char* filePath, GLenum param1, GLenum param2, GLuint alphaEnabled) {

/* Texture 1 */
/* Create texture object and store it in the texture variable */
    glGenTextures(1, texture);

/* Bind texture object */
    glBindTexture(GL_TEXTURE_2D, *texture);

/* Set texture filtering/wrapping options for the currently bound texture object */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param2);

    stbi_set_flip_vertically_on_load(true);

    /* Generate textures from currently bound texture object */
    if(alphaEnabled){
        data = stbi_load(filePath, &width, &height, &nrChannels, STBI_rgb_alpha);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
    }
    else{
        data = stbi_load(filePath, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
    }

    stbi_image_free(data);
}