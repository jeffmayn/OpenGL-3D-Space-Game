//
// Created by chris on 12.12.2017.
//

#include <utility>

#include "mesh.h"

void Mesh::Draw(Shader shader) {

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;
    GLuint ambientNr = 1;
    GLuint shininessNr = 1;

//    std::cout << textures.size() << std::endl;

    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
        } else if (name == "texture_ambient") {
            number = std::to_string(ambientNr++);
        } else if (name == "texture_height") {
            number = std::to_string(heightNr++);
        } else if (name == "texture_shininess"){
            number = std::to_string(shininessNr++);
        }
//        std::cout << "name: " << name << " " << number << std::endl;
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        if(name != "texture_shininess"){
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLint)indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, BiTangent));

    glBindVertexArray(0);
}
