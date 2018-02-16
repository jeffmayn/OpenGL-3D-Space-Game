//
// Created by chris on 28.11.2017.
//

#ifndef LEARN_OPENGL_CALLBACKS_H
#define LEARN_OPENGL_CALLBACKS_H

#include "../include/irrKlang/irrKlang.h"
#include "../../include/glad/glad/glad.h"
#include "../../include/GLFW/glfw3.h"
#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"

#include "../IO/controls.h"
#include "../IO/camera.h"


extern unsigned int SCR_WIDTH, SCR_HEIGHT, refreshRate;
extern const unsigned int WIN_WIDTH, WIN_HEIGHT;

extern double initX, initY;
extern double heightRatio, widthRatio;
extern Camera camera;
extern bool windowedMode;
extern bool mouseInit;
extern bool wireframeEnabled;
extern bool focusEnabled;
extern bool soundEnabled;
extern irrklang::ISoundEngine* eng;

void setCamera(Camera camObj, irrklang::ISoundEngine *engine);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double offsetX, double offsetY);
void special_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);



#endif //LEARN_OPENGL_CALLBACKS_H
