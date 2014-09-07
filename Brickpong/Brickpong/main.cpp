#include "main.h"

BrickpongGame* brickpongGame;

void BrickpongCursorPositionCallback(GLFWwindow* window, double x, double y) {
    brickpongGame->GetInput()->CursorPositionChanged(brickpongGame, window, x, y);
}

void BrickpongKeyboardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    brickpongGame->GetInput()->KeyCallback(brickpongGame, window, key, scancode, action, mods, BrickpongCursorPositionCallback);
}

int main(void) {
    try {
        unsigned short debugMode = 1;
        GraphicsEngine* graphicsEngine = new GraphicsEngine();

        Window* window = new Window(940, 560, "Brickpong", false);
        window->makeContextCurrent();

        GameEngine* gameEngine = new GameEngine(window, debugMode);

        bool play = true;
        int currentGame = 0;
        do {
            if (gameEngine->Run(&currentGame, graphicsEngine, NULL, NULL)) {
                switch (currentGame) {
                    case 0: {

                        brickpongGame = new BrickpongGame(debugMode);
                        gameEngine->RunBrickpong(graphicsEngine, BrickpongCursorPositionCallback, BrickpongKeyboardKeyCallback, brickpongGame);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            else {
                play = false;
            }
        } while (play);

        delete window;

        exit(EXIT_SUCCESS);
    }
    catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        std::cout << "PRESS ENTER TO CLOSE" << std::endl;
        getchar();
        exit(EXIT_FAILURE);
    }
}