//
// Created by christian on 12/22/17.
//

#include "shape.h"
#include "glm/gtc/matrix_transform.hpp"

Shape::Shape(Shader *shader, Model *model, glm::mat4 view, glm::mat4 projection) {
    this->shader = shader;
    this->object = model;
    this->view = view;
    this->projection = projection;
}

void Shape::Move(GLfloat xPos, GLfloat yPos, GLfloat zPos) {
    shader->use();
    glm::vec3 pos(xPos, yPos, zPos);
    model = glm::translate(model, pos);
}

void Shape::Scale(GLfloat multiplier, Axis axis) {
    shader->use();
    glm::vec3 vec = glm::vec3();
    if (axis == AXIS_X){
        vec = {1.0, 0.0, 0.0};
    }else if (axis == AXIS_Y){
        vec = {0.0, 1.0, 0.0};
    }else if (axis == AXIS_Z){
        vec = {0.0, 0.0, 1.0};
    }else if (axis == AXIS_XY){
        vec = {1.0, 1.0, 0.0};
    }else if (axis == AXIS_XZ){
        vec = {1.0, 0.0, 1.0};
    }else if (axis == AXIS_YZ){
        vec = {0.0, 1.0, 1.0};
    }else if (axis == AXIS_XYZ){
        vec = {1.0, 1.0, 1.0};
    }
    vec = multiplier * vec;
    if(vec.x == 0.0f){
        vec.x = 1.0f;
    }
    if(vec.y == 0.0f){
        vec.y = 1.0f;
    }
    if(vec.z == 0.0f){
        vec.z = 1.0f;
    }

    model = glm::scale(model, vec);

}

void Shape::Rotate(GLfloat angle, Axis axis) {
    shader->use();
    glm::vec3 vec;
    if (axis == AXIS_X){
        vec = {1.0, 0.0, 0.0};
    }else if (axis == AXIS_Y){
        vec = {0.0, 1.0, 0.0};
    }else if (axis == AXIS_Z){
        vec = {0.0, 0.0, 1.0};
    }else if (axis == AXIS_XY){
        vec = {1.0, 1.0, 0.0};
    }else if (axis == AXIS_XZ){
        vec = {1.0, 0.0, 1.0};
    }else if (axis == AXIS_YZ){
        vec = {0.0, 1.0, 1.0};
    }else if (axis == AXIS_XYZ){
        vec = {1.0, 1.0, 1.0};
    }
    model = glm::rotate(model, glm::radians(angle), vec);
}

void Shape::Render() {
    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    object->Draw(*shader);
}
