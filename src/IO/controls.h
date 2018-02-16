//
// Created by chris on 28.11.2017.
//

#ifndef LEARN_OPENGL_INPUT_H
#define LEARN_OPENGL_INPUT_H

#include "../misc/callbacks.h"

#include "../../include/GLFW/glfw3.h"
#include "../../include/glm/glm.hpp"
#include <iostream>

extern float deltaTime;
extern float lastFrame;
extern float currentFrame;

glm::vec3 getPos();
glm::vec3 getRot();
glm::vec3 getDir();
glm::vec3 getDir2();
void dampenRot();

void setNewDirection(glm::vec3 dir);
void followMouse(float x, float y);

void processInput(GLFWwindow* window);
void updateDeltaTime();

#endif //LEARN_OPENGL_INPUT_H
