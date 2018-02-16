//
// Created by jonas on 12/23/17.
//
#include "CollisionDetection.h"

#include "../IO/controls.h"


bool collision;

std::vector<glm::vec3> imoveables;
int countObjects;

bool Detect(glm::vec3 pos, glm::vec3 direction, float size) {
    int closest;

    float d;
    for (int e = 0; e < countObjects; e++) {
        d=glm::distance(pos,imoveables[e]);

//        std::cout << "Distance to enemy!" << d << std::endl;
        if(d <= size){
            glm::vec3 relativeDir = pos-imoveables[e];
            std::cout  << "Proximity alert!!" << std::endl;

            setNewDirection(getNewDirection(relativeDir, direction));
//            std::cout << "During detection: " << d << std::endl;
//            collision = true;
            return true;
        }
    }
    return false;
}

glm::vec3 getNewDirection(glm::vec3 relativeDir, glm::vec3 direction){
    return glm::normalize(glm::cross(glm::cross(relativeDir, direction), relativeDir));
};

void setImoveable(glm::vec3 m) {
    imoveables.push_back(m);
    countObjects++;
}