//
// Created by qwerty on 12/17/17.
//

#ifndef LEARN_OPENGL_TEXT_H
#define LEARN_OPENGL_TEXT_H

#include "../../include/glad/glad/glad.h"
#include "../../include/glm/glm.hpp"

struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text {
public:
    Text(GLuint width, GLuint height, const GLchar* vPath, const GLchar* fPath);
    Shader shader;
    void RenderText(std::string text, GLfloat xPos, GLfloat yPos, GLfloat scale, glm::vec3 color);
    void GenerateText(const GLchar* path);
private:
    GLuint VAO, VBO;
    std::map<GLchar, Character> Characters;
};



#endif //LEARN_OPENGL_TEXT_H
