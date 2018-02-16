//
// Created by christian on 12/21/17.
//

#include "window.h"

void Window::createContext() {
    glfwMakeContextCurrent(window);
}

void Window::switchMode() {
    if(windowed){
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, REFRESH_RATE);
        windowed = GL_FALSE;
    }
    else {
        glfwSetWindowMonitor(window, nullptr, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, REFRESH_RATE);
        windowed = GL_TRUE;
    }
}