//
// Created by chris on 28.11.2017.
//

#ifndef LEARN_OPENGL_MAIN_H
#define LEARN_OPENGL_MAIN_H

/** SYSTEM HEADERS */
#include <map>
#include <iostream>
#include <cmath>

/** EXTERNAL HEADERS */
#include "../include/glad/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/stb/stb_image.h"
#include "../include/glad/glad.c"
#include "../include/ft2build.h"
#include "../include/irrKlang/irrKlang.h"

/** EXTERNAL HEADER GUARDS */

#include FT_FREETYPE_H

/** LOCAL HEADERS */
#include "misc/callbacks.h"
#include "IO/controls.h"
#include "IO/camera.h"
#include "shader/shader.h"
#include "render/texture.h"
#include "render/model.h"
#include "render/text.h"
#include "data/vertices.h"
#include "collision/CollisionDetection.h"

// FreeType

extern bool mouseInit;

#endif //LEARN_OPENGL_MAIN_H
