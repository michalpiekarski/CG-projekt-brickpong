#include "GameEngine.h"

GameEngine::GameEngine(Window* awindow) {
    _window = awindow;
    _debugMode = 0;
}

GameEngine::GameEngine(Window* awindow, unsigned short adebugMode) : GameEngine(awindow) {
    _debugMode = adebugMode;
}

GameEngine::~GameEngine() {

}

void GameEngine::RunBrickpong(GraphicsEngine* agraphicsEngine, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback, BrickpongGame* abrickpongGame) {
    _window->setCursorMode(GLFW_CURSOR_HIDDEN);
    _window->setStickyKeys(GL_TRUE);
    _window->setCursorPosCallback(acursorPositionCallback);
    _window->setKeyCallback(akeyCallback);

    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgram* shaderSemiTransparentProgram = new ShaderProgram();
    Shader* vShader = new Shader("shaders/Simple.vert", GL_VERTEX_SHADER);
    Shader* fShader = new Shader("shaders/Simple.frag", GL_FRAGMENT_SHADER);
    Shader* fShaderSemiTransparent = new Shader("shaders/SemiTransparentSimple.frag", GL_FRAGMENT_SHADER);

    shaderProgram->attachShader(vShader);
    shaderProgram->attachShader(fShader);
    shaderProgram->bindFragDataLocation(0, "fragData");
    shaderProgram->link();

    shaderSemiTransparentProgram->attachShader(vShader);
    shaderSemiTransparentProgram->attachShader(fShaderSemiTransparent);
    shaderSemiTransparentProgram->bindFragDataLocation(0, "fragData");
    shaderSemiTransparentProgram->link();

    delete vShader;
    delete fShader;
    delete fShaderSemiTransparent;

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint MatrixID = shaderProgram->getUniformLoc("MVP");

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 View = agraphicsEngine->ZoomIn();
    glm::mat4 Projection = agraphicsEngine->ChangeToPerspective();

    glm::mat4 tmpModel, tmpMVP;

    GLint positionAttribLoc = shaderProgram->getAttributeLoc("position");
    GLint colorAttribLoc = shaderProgram->getAttributeLoc("color");

    abrickpongGame->CreateGame(shaderProgram, positionAttribLoc, colorAttribLoc, shaderProgram, positionAttribLoc, colorAttribLoc, shaderSemiTransparentProgram, positionAttribLoc, colorAttribLoc);

    std::cout << "Points: " << abrickpongGame->GetPoints() << std::endl;

    GLint viewportWidth, viewportHeight;


    double lastTime;
    int nbFrames;

    if (_debugMode > 0) {
        lastTime = glfwGetTime();
        nbFrames = 0;
    }

    do {
        View = agraphicsEngine->ChangeZoomLevel(_window, View);

        abrickpongGame->GetWorld()->Step();
        abrickpongGame->DestroyBricks();

        if (_debugMode > 0) {
            double currentTime = glfwGetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0) {
                std::cout << 1000.0 / double(nbFrames) << "ms/frame" << std::endl;
                nbFrames = 0;
                lastTime += 1.0;
            }
        }

        _window->getFrameBufferSize(&viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (agraphicsEngine->IsZoomed()) {
            // Bricks
            abrickpongGame->DrawBricks(Model, View, Projection, MatrixID);

            // Pad
            abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), Model, View, Projection, MatrixID);

            // Ball
            abrickpongGame->GetBall()->Draw(Model, View, Projection, MatrixID);
        }
        else {
            glm::vec3 sceneOffset;
            for (float i = 90.0f; i >= -90.0f; i -= 90.0f) {
                switch ((int)i) {
                    case -90:
                        sceneOffset = glm::vec3(10.0f, 0.0f, -35.0f);
                        break;
                    case 0:
                        sceneOffset = glm::vec3();
                        break;
                    case 90:
                        sceneOffset = glm::vec3(-10.0f, 0.0f, -35.0f);
                        break;
                }
                Model = glm::rotate(Model, glm::radians(i), glm::vec3(0.0f, 1.0f, 0.0f));
                Model = glm::translate(Model, sceneOffset);
                // Bricks
                abrickpongGame->DrawBricks(Model, View, Projection, MatrixID);

                // Pad
                abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), Model, View, Projection, MatrixID);

                // Ball
                abrickpongGame->GetBall()->Draw(Model, View, Projection, MatrixID);

                Model = glm::mat4(1.0f);
            }
        }

        _window->swapBuffers();

        abrickpongGame->CheckGameResult();
        glfwPollEvents();
    } while (_window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS && _window->shouldClose() == 0);

    delete abrickpongGame;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete shaderProgram;
}