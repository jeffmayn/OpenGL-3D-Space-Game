cmake_minimum_required(VERSION 3.5)

project(battleground_IMADA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
        src/main.cpp
        src/misc/callbacks.cpp
        src/misc/callbacks.h
        src/IO/controls.cpp
        src/IO/controls.h
        src/main.h
        src/shader/shader.h
        src/shader/shader.cpp
        include/stb/stb_image.h
        include/stb/stb_image.cpp
        src/render/texture.cpp
        src/render/texture.h
        src/data/vertices.h
        src/IO/camera.cpp
        src/IO/camera.h
        src/render/mesh.cpp
        src/render/mesh.h
        src/render/model.cpp
        src/render/model.h
        include/stb/stb_image.cpp
        src/render/text.h
        src/render/text.cpp
        include src/utility/window.cpp src/utility/window.h src/utility/shape.cpp src/utility/shape.h src/collision/CollisionDetection.cpp src/collision/CollisionDetection.h)


find_package(OpenGL REQUIRED)

#HEADER FILES

find_path(assimp_INCLUDE NAMES "scene.h" PATHS ${PROJECT_SOURCE_DIR}/include/assimp NO_DEFAULT_PATH)
if(NOT assimp_INCLUDE)
    message(FATAL_ERROR "Cannot find ${assimp_INCLUDE}")
endif()

find_path(IrrKlang_INCLUDE NAMES "irrKlang.h" PATHS ${PROJECT_SOURCE_DIR}/include/irrKlang NO_DEFAULT_PATH)
if(NOT IrrKlang_INCLUDE)
    message(FATAL_ERROR "Cannot find ${IrrKlang_INCLUDE}")
endif()

find_path(freetype_INCLUDE NAMES "freetype.h" PATHS ${PROJECT_SOURCE_DIR}/include/freetype NO_DEFAULT_PATH)
if(NOT freetype_INCLUDE)
    message(FATAL_ERROR "Cannot find ${freetype_INCLUDE}")
endif()

find_path(glfw3_INCLUDE NAMES "glfw3.h" PATHS ${PROJECT_SOURCE_DIR}/include/GLFW NO_DEFAULT_PATH)
if(NOT glfw3_INCLUDE)
    message(FATAL_ERROR "Cannot find ${glfw3_INCLUDE}")
endif()

#LIBRARIES

find_library(freetype_LIB NAMES "libfreetype.a" PATHS ${PROJECT_SOURCE_DIR}/lib/freetype NO_DEFAULT_PATH)
if(NOT freetype_LIB)
    message(FATAL_ERROR "Cannot find ${freetype_LIB}")
endif()

find_library(IrrKlang_LIB NAMES "libIrrKlang.so" PATHS ${PROJECT_SOURCE_DIR}/lib/irrKlang NO_DEFAULT_PATH)
if(NOT IrrKlang_LIB)
    message(FATAL_ERROR "Cannot find ${IrrKlang_LIB}")
endif()

find_library(glfw3_LIB NAMES "libglfw.so" PATHS ${PROJECT_SOURCE_DIR}/lib/GLFW NO_DEFAULT_PATH)
if(NOT glfw3_LIB)
    message(FATAL_ERROR "Cannot find ${glfw3_LIB}")
endif()

find_library(assimp_LIB NAMES "libassimp.so" PATHS ${PROJECT_SOURCE_DIR}/lib/assimp NO_DEFAULT_PATH)
if(NOT assimp_LIB)
    message(FATAL_ERROR "Cannot find ${assimp_LIB}")
endif()

IF(CMAKE_BUILD_TYPE MATCHES "Debug" OR "debug" OR "DEBUG" OR DEBUG)
    message("Debug: Moving binaries to bin/debug post-compile.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/debug)
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES "Release" OR "release" OR "RELEASE" OR RELEASE)
    message("Release: Moving binaries to bin/debug post-compile.")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/release)
ENDIF()

file(COPY src/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("Copying src/assets to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

file(COPY src/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("Copying src/data to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_executable(battleground_IMADA ${SOURCE_FILES})

include_directories(
            include
            ${PROJECT_INCLUDE_DIR}/assimp
            ${PROJECT_INCLUDE_DIR}/GLFW
            ${PROJECT_INCLUDE_DIR}/glm
            ${PROJECT_INCLUDE_DIR}/glad
            ${PROJECT_INCLUDE_DIR}/GLFW
            ${PROJECT_INCLUDE_DIR}/irrKlang
            ${PROJECT_INCLUDE_DIR}/stb
            ${PROJECT_INCLUDE_DIR}/freetype)

if(WIN32 OR WIN64 AND NOT UNIX)
    include_directories(${OPENGL_INCLUDE_DIRS}
            ${assimp_INCLUDE}
            ${glfw3_INCLUDE}
            ${IrrKlang_INCLUDE}
            ${freetype_INCLUDE}
            include
            )

    target_link_libraries(battleground_IMADA
            ${OPENGL_LIBRARIES}
            ${glfw3_LIB}
            ${assimp_LIB}
            ${IrrKlang_LIB}
            ${freetype_LIB}
            assimp)
endif()

if(UNIX)
    include_directories(
            ${OPENGL_INCLUDE_DIRS}
            ${assimp_INCLUDE}
            ${glfw3_INCLUDE}
            ${IrrKlang_INCLUDE}
            ${freetype_INCLUDE}
            include)

    target_link_libraries(battleground_IMADA
            ${OPENGL_LIBRARIES}
            ${glfw3_LIB}
            ${assimp_LIB}
            ${IrrKlang_LIB}
            ${freetype_LIB}
            dl)
endif()
IF(UNIX)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../lib:\$ORIGIN")
ENDIF()

install(TARGETS battleground_IMADA RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}bin/debug CONFIGURATIONS Debug)
