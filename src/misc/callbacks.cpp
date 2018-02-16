//
// Created by chris on 28.11.2017.
//

#include <iostream>

#include "callbacks.h"

#include "../utility/window.h"

unsigned int SCR_WIDTH, SCR_HEIGHT, refreshRate;
const unsigned int WIN_WIDTH = 800, WIN_HEIGHT = 600;

double initX, initY;
double heightRatio, widthRatio;
bool windowedMode = true;
bool mouseInit = true;
bool wireframeEnabled = false;
bool focusEnabled = false;
bool soundEnabled = true;
float volume = 0.1;
irrklang::ISoundEngine* eng;

void setCamera(Camera camObj, irrklang::ISoundEngine* engine) {
    camera = camObj;
    eng = engine;
    initX = WIN_WIDTH;
    initY = WIN_HEIGHT;
    heightRatio = SCR_HEIGHT/(double)WIN_HEIGHT;
    widthRatio = SCR_WIDTH/(double)WIN_HEIGHT;
    std::cout << "Width ratio of " << widthRatio << " and height ratio of " << heightRatio << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {

    if(mouseInit){
        initX = xPos;
        initY = yPos;
        mouseInit = false;
    }

    double offsetX = xPos - initX;
    double offsetY = initY - yPos;
    initX = xPos;
    initY = yPos;

    camera.ProcessMouseMovement((float) offsetX, (float) offsetY);
}

void scroll_callback(GLFWwindow* window, double offsetX, double offsetY)
{
    camera.ProcessMouseScroll((float) offsetY);
}


void special_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F1) {
        if (action == GLFW_PRESS) {
            if (windowedMode) {
                glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GL_DONT_CARE);
                windowedMode = false;
            } else {
                glfwSetWindowMonitor(window, nullptr, WIN_WIDTH / 2, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT,
                                     GL_DONT_CARE);
                windowedMode = true;
            }
        }
    }

    if(key == GLFW_KEY_F2 && action == GLFW_PRESS){
        if(wireframeEnabled){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireframeEnabled = false;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireframeEnabled = true;
        }
    }
    if(key == GLFW_KEY_F3 && action == GLFW_PRESS){
        if(focusEnabled){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            focusEnabled = false;
        }
        else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            focusEnabled = true;
        }
    }

    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        if (soundEnabled) {
            eng->setAllSoundsPaused(true);
            soundEnabled = false;
            std::cout << "sound off" << std::endl;
        } else {
            eng->setAllSoundsPaused(false);
            soundEnabled = true;
            std::cout << "sound on" << std::endl;
        }
    }

    if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {
        if (volume < 0.1) {
            volume = 0.0;
        } else
            volume-=0.1;
            eng->setSoundVolume(volume);
            std::cout << "Volume: " << eng->getSoundVolume() << std::endl;
        } else if (key == GLFW_KEY_F7 && action == GLFW_PRESS) {
            if (volume > 1.0) {
                volume = 1.0;
    } else {
        volume+=0.1;
        eng->setSoundVolume(volume);
        std::cout << "Volume: " << eng->getSoundVolume() << std::endl;
    }
        }
}

