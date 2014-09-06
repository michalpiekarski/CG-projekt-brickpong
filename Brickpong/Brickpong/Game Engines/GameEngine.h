#ifndef __Brickpong__GameEngine__
#define __Brickpong__GameEngine__

#include <string>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include "../Graphics Engine/GraphicsEngine.h"
#include "Brickpong/BrickpongGame.h"

    // TODO: Zaimplementowac mechanizmy sterowania grami: wybieranie gry, generowanie leveli, itd. Dodatkowo okreslić mechanizmy zmiany systemów sterowania między grami i środowiskiem "poza grą".

class GameEngine {
private:
    Window* _window;
    unsigned short _debugMode;
public:
    GameEngine(Window* awindow);
    GameEngine(Window* awindow, unsigned short adebugMode);
    virtual ~GameEngine();
    bool Run(int* acurrentGame, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback);
    void RunBrickpong(GraphicsEngine* agraphicsEngine, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback, BrickpongGame* abrickpongGame);
};

#endif /* defined(__Brickpong__GameEngine__) */