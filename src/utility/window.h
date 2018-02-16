//
// Created by christian on 12/21/17.
//

#ifndef LEARN_OPENGL_WINDOW_H
#define LEARN_OPENGL_WINDOW_H

#include <string>
#include <iostream>

#include "../../include/glad/glad/glad.h"
#include "../../include/GLFW/glfw3.h"

enum GLMode {
    GL_WINDOWED_MODE,
    GL_FULLSCREEN_MODE
};
enum GLVersionMinor {
    GL_MINOR_1 = 1,
    GL_MINOR_2 = 2,
    GL_MINOR_3 = 3,
    GL_MINOR_4 = 4,
    GL_MINOR_5 = 5,
    GL_MINOR_6 = 6,
    GL_MINOR_7 = 7,
    GL_MINOR_8 = 8,
    GL_MINOR_9 = 9
};
enum GLVersionMajor {
    GL_MAJOR_3 = 3,
    GL_MAJOR_4 = 4
};
enum Profile {
    GL_CORE = GLFW_OPENGL_CORE_PROFILE,
    GL_COMPAT = GLFW_OPENGL_COMPAT_PROFILE
};

class Window {
public:
    Window(const char* title, GLMode mode, GLVersionMajor major, GLVersionMinor minor, Profile profile){

        glfwInit();
        glfwWindowHint(GL_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        this->mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        SCREEN_WIDTH    = (GLuint) this->mode->width;
        SCREEN_HEIGHT   = (GLuint) this->mode->height;
        REFRESH_RATE    = (GLuint) this->mode->refreshRate;

        if(mode == GL_WINDOWED_MODE){
            this->width = SCREEN_WIDTH/2;
            this->height = SCREEN_HEIGHT/2;
            window = glfwCreateWindow(width, height, title, nullptr, nullptr);
            windowed = GL_TRUE;
        }
        else if(mode == GL_FULLSCREEN_MODE){
            this->width = width;
            this->height = height;
            window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, glfwGetPrimaryMonitor(), nullptr);
            windowed = GL_FALSE;
        }
        else {
            std::cout << "ERROR: No mode specified, cannot continue." << std::endl;
            success = GL_FALSE;
            return;
        }
        if(window == nullptr){
            std::cout << "ERROR: Could not create window, cannot continue." << std::endl;
            glfwTerminate();
            success = GL_FALSE;
            return;
        }

    }

    void createContext();
    void switchMode();

    GLuint SCREEN_WIDTH, SCREEN_HEIGHT, REFRESH_RATE;
    const GLFWvidmode* mode;
    GLFWwindow* window;
    GLuint width, height;
    GLboolean windowed;
    GLboolean success = GL_TRUE;

private:

};


#endif //LEARN_OPENGL_WINDOW_H
