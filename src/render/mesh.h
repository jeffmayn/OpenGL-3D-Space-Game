//
// Created by chris on 12.12.2017.
//

#ifndef LEARN_OPENGL_MESH_H
#define LEARN_OPENGL_MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../../include/glm/vec2.hpp"
#include "../../include/glm/vec3.hpp"

#include "../shader/shader.h"

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 BiTangent;
};

struct Texture {
    unsigned int id;
    string type, path;
};

class Mesh {
public:
    unsigned int VAO;
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  Functions  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
        this -> vertices = vertices;
        this -> indices = indices;
        this -> textures = textures;
        setupMesh();
    }
    void Draw(Shader shader);
private:
    /*  Render data  */
    unsigned int VBO, EBO;
    /*  Functions    */
    void setupMesh();
};



#endif //LEARN_OPENGL_MESH_H
