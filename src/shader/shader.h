//
// Created by chris on 28.11.2017.
//

#ifndef LEARN_OPENGL_SHADER_H
#define LEARN_OPENGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../include/glad/glad/glad.h"
#include "../../include/glm/glm.hpp"

class Shader{
public:
    /** Program ID */
    GLuint ID;

    /** Constructor, reads and builds shader */
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

    /** Activates shader */
    void use();

    /** Utility uniform functions */
    void setBool(const std::string &name, bool value) const;
// ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;
// ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;
// ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
// ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
// ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
// ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
// ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
// ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};
#endif //LEARN_OPENGL_SHADER_H
