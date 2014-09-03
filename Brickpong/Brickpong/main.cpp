#include "main.h"

// Uncomment for debug output in console
#define __Brickpong__DEBUG_LOG__

BrickpongGame* brickpongGame;

void BrickpongCursorPositionCallback(GLFWwindow* window, double x, double y) {
    brickpongGame->GetInput()->CursorPositionChanged(brickpongGame, window, x, y);
}

void BrickpongKeyboardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    brickpongGame->GetInput()->KeyCallback(brickpongGame, window, key, scancode, action, mods, BrickpongCursorPositionCallback);
}

int main(void) {
    try {
        GraphicsEngine* graphicsEngine = new GraphicsEngine();

        Window* window = new Window(960, 540, "Brickpong", false);
        
        GameEngine* gameEngine = new GameEngine(window);

        brickpongGame = new BrickpongGame();
        gameEngine->RunBrickpong(graphicsEngine, BrickpongCursorPositionCallback, BrickpongKeyboardKeyCallback, brickpongGame);

        delete window;

        return 0;
    }
    catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}