#include "main.h"

// Uncomment for debug output in console
#define __Brickpong__DEBUG_LOG__

BrickpongGame* brickpongGame;

void CursorPositionCallback(GLFWwindow* window, double x, double y) {
    brickpongGame->GetInput()->CursorPositionChanged(brickpongGame, window, x, y);
}

void KeyboardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    brickpongGame->GetInput()->KeyCallback(brickpongGame, window, key, scancode, action, mods, CursorPositionCallback);
}

int main(void) {
    try {
        GraphicsEngine* graphicsEngine = new GraphicsEngine();
        brickpongGame = new BrickpongGame();

        Window* window = new Window(960, 540, "Brickpong", false);
        
        GameEngine* gameEngine = new GameEngine(window);

        gameEngine->RunBrickpong(graphicsEngine, CursorPositionCallback, KeyboardKeyCallback, brickpongGame);

        delete window;

        return 0;
    }
    catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}