//
// Created by christian on 12/22/17.
//

#ifndef LEARN_OPENGL_SHAPE_H
#define LEARN_OPENGL_SHAPE_H


#include "../shader/shader.h"
#include "../render/model.h"

enum Axis {
    AXIS_X,
    AXIS_Y,
    AXIS_Z,
    AXIS_XY,
    AXIS_XZ,
    AXIS_YZ,
    AXIS_XYZ
};

class Shape {
public:
    Shape(Shader *shader, Model *model, glm::mat4 view, glm::mat4 projection);
    void Move(GLfloat xPos, GLfloat yPos, GLfloat zPos);
    void Scale(GLfloat multiplier, Axis axis);
    void Rotate(GLfloat angle, Axis axis);
    void Render();

private:
    Shader* shader;
    Model* object;

    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;
};


#endif //LEARN_OPENGL_SHAPE_H
