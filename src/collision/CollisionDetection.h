//
// Created by jonas on 12/23/17.
//

#ifndef LEARN_OPENGL_COLLISIONDETECTION_H
#define LEARN_OPENGL_COLLISIONDETECTION_H


#include "glad/glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"
#include <vector>
#include <cmath>
#include <map>
#include <math.h>
#include <iostream>

extern std::vector<glm::vec3> imoveables;
extern int countObjects;
bool Detect(glm::vec3 pos, glm::vec3 direction, float size);

void setImoveable(glm::vec3 m);
glm::vec3 getNewDirection(glm::vec3 relativeDir, glm::vec3 direction);


#endif //LEARN_OPENGL_COLLISIONDETECTION_H
