#ifndef __Brickpong__main__
#define __Brickpong__main__

#include <iostream>

#ifdef _WIN32
    #include <GL/glew.h>
    #ifndef GLFW_DLL
        #define GLFW_DLL
    #endif /* defined(GLFW_DLL) */
#endif /* included(GL/glew.h) */
#ifdef __APPLE__
    #ifndef GLFW_INCLUDE_GLCOREARB
        #define GLFW_INCLUDE_GLCOREARB
    #endif /* defined(GLFW_INCLUDE_GLCOREARB) */
#endif
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "BrickpongException.h"
#include "Graphics Engine/Graphics Engine.h"
#include "Physics Engine/Physics Engine.h"

void CreateBuffers(VBO* vVBO, VBO* cVBO, EBO* myEBO);

void Draw(EBO* myEBO);

void cursorPositionChanged(GLFWwindow *window, double x, double y);

void ResetGame();

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

void CheckBallBoundsCol();

void CheckBallPadCol();

bool CheckBallBrickCol(float brickX, float brickY);

void CheckGameWin();

#endif /* defined(__Brickpong__main__) */