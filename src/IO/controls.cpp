//
// Created by chris on 28.11.2017.
//

#include "controls.h"

#include "../collision/CollisionDetection.h"

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame;
// variables for moving the battlecruiser

float speed = 0.0f,
        maxSpeed = 1.0f,
        acceleration = 0.002f,
        breakPoint = 0.02f,
        breakSpeed = 0.008f;

float turn = 0.0008, turnBreak = 0.002;
glm::vec3 turnRateXY = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 turnXY = glm::vec3();

glm::vec3 direction = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));
glm::vec3 pos = glm::vec3(-20.0f, 20.0f, -10.0f);
glm::vec3 tempVec;
glm::vec3 lastPos;




void processInput(GLFWwindow* window){

//    cameraSpeed = 4.5f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if(speed < maxSpeed){
            speed -= acceleration;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if(speed > -maxSpeed){
            speed += acceleration;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    }
//    if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
//        speed += acceleration + 0.0008;
//    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
    }
    //    movement.update(deltaTime);

    // --- adds drag and stops movement under threshold/breakPoint
    if(!(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS | glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)){
        if(speed < breakPoint && speed > -breakPoint){
            speed = 0;
        }
        if(speed > 0){
            speed -= breakSpeed;
        }
        if(speed < 0){
            speed += breakSpeed;
        }
    }

    // slows down the rotation
    dampenRot();

    turnXY+=turnRateXY;

    // translates the model rotation to the movement rotation
    direction.z = (float) (cos(glm::radians(turnXY.x)) * cos(glm::radians(turnXY.y)));
    direction.y = (float) (sin(glm::radians(turnXY.y)));
    direction.x = (float) (sin(glm::radians(turnXY.x)) * cos(glm::radians(turnXY.y)));
    direction = glm::normalize(direction);
    lastPos=pos;
    if(Detect(pos, direction , 3)){
//        turnRateXY = glm::vec3(0.0f, 0.0f, 0.0f);
        turnXY.x = glm::degrees(direction.x);
        turnXY.y = glm::degrees(direction.z); // (float) acos(direction.z);

        pos = lastPos + speed * (direction * glm::vec3(1.0f, -1.0f, 1.0f));
//        std::cout<<"hovhov bandit"<< std::endl;
    }
    else {
        pos += speed * (direction * glm::vec3(1.0f, -1.0f, 1.0f));
    }

}
void updateDeltaTime(){
    currentFrame = (float) glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
glm::vec3 getPos(){
    return pos;
}
glm::vec3 getRot(){
    return turnXY;
}
glm::vec3 getDir(){
    return direction * -1.0f;
}

void followMouse(float x, float y){
    turnRateXY.x-=x*0.02;
    turnRateXY.y+=y*0.02;

//    std::cout<<"x:"<< turnRateXY.x << "  y: "<< turnRateXY.y <<std::endl;
}
void dampenRot(){
    if(turnRateXY.x > turnBreak){
        turnRateXY.x -=turnBreak;
    }
    if(turnRateXY.y > turnBreak){
        turnRateXY.y -=turnBreak;
    }
    if(turnRateXY.x < -turnBreak){
        turnRateXY.x +=turnBreak;
    }
    if(turnRateXY.y < -turnBreak){
        turnRateXY.y +=turnBreak;
    }

    if(turnRateXY.x < turnBreak && turnRateXY.x > -turnBreak){
        turnRateXY.x =0;
    }
    if(turnRateXY.y < turnBreak && turnRateXY.y > -turnBreak){
        turnRateXY.y =0;
    }
}
void setNewDirection(glm::vec3 dir){
    direction=dir;
}