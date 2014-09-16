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

bool GameEngine::Run(int* acurrentGame, GraphicsEngine* agraphicsEngine, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback) {
    bool playGame = true;

    _window->setCursorMode(GLFW_CURSOR_HIDDEN);
    _window->setStickyKeys(GL_TRUE);
    _window->setCursorPosCallback(acursorPositionCallback);
    _window->setKeyCallback(akeyCallback);

    ShaderProgram* shaderProgram = new ShaderProgram();
    Shader* vShader = new Shader("shaders/ASSIMP.vert", GL_VERTEX_SHADER);
    Shader* fShader = new Shader("shaders/ASSIMP.frag", GL_FRAGMENT_SHADER);
    shaderProgram->attachShader(vShader);
    shaderProgram->attachShader(fShader);
    shaderProgram->bindFragDataLocation(0, "fragData");
    shaderProgram->link();
    delete vShader;
    delete fShader;
    shaderProgram->use();

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint modelUniformLoc = shaderProgram->getUniformLoc("Model");
    GLuint viewUniformLoc = shaderProgram->getUniformLoc("View");
    GLuint projectionUniformLoc = shaderProgram->getUniformLoc("Projection");

    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec2 cursorPosition = _window->getCursorPositionInWorldSpace(60.0f, 2.0f, glm::vec2(0.0f, 0.0f));
    glm::vec3 viewTarget = glm::vec3(cursorPosition.x, cursorPosition.y-2.0f, glm::abs(cursorPosition.x));
    glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 1.0f, 30.0f), viewTarget, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Projection = glm::perspective(120.0f, 16.0f / 9.0f, 0.01f, 10000.0f);
    glUniformMatrix4fv(projectionUniformLoc, 1, GL_FALSE, &Projection[0][0]);

    glm::mat4 tmpModel, tmpMVP;

    shaderProgram->use();
    VAO* vao = new VAO();
    vao->bind();

    VBO* vvbo = new VBO();
    VBO* cvbo = new VBO();
    VBO* nvbo = new VBO();
    EBO* ebo = new EBO();

    if (!agraphicsEngine->Load3DFile("meshes/arcade.fbx", shaderProgram, ebo, vvbo, cvbo, nvbo)) {
        exit(EXIT_FAILURE);
    }

    GLint viewportWidth, viewportHeight;

    double lastTime = 0;
    int nbFrames = 0;

    if (_debugMode > 0) {
        lastTime = glfwGetTime();
        nbFrames = 0;
    }

    Text* textRenderer = new Text(_window, "fonts/Zapfino.ttf", 1);
    GLfloat textColorWhite[4] = {
        1.0, 1.0f, 1.0f, 1.0f,
    };
    GLfloat textColorRed[4] = {
        1.0f, 0.0f, 0.0f, 1.0f
    };

    float rotation = 0;
    glm::vec3 rotationX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 rotationY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 rotationZ = glm::vec3(0.0f, 0.0f, 1.0f);
    do {
        shaderProgram->use();
        
        cursorPosition = _window->getCursorPositionInWorldSpace(60.0f, 2.0f, glm::vec2(0.0f, 0.0f));
        viewTarget = glm::vec3(cursorPosition.x, cursorPosition.y-2.0f, glm::abs(cursorPosition.x));
        View = glm::lookAt(glm::vec3(0.0f, 1.0f, 30.0f), viewTarget, glm::vec3(0.0f, 1.0f,0.0f));
        glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, &View[0][0]);

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

        glm::vec3 translation, scale;
        glm::mat4 tmpModel, MVP;

        // FRONT
        translation = glm::vec3(0.0f, 0.0f, 10.0f);
        //scale = glm::vec3(2.0f, 5.0f, 2.0f);
        scale = glm::vec3(0.25f, 0.25f, 0.25f);
        tmpModel = glm::translate(Model, translation);
        tmpModel = glm::rotate(tmpModel, glm::radians(rotation), rotationY);
        tmpModel = glm::scale(tmpModel, scale);
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, &tmpModel[0][0]);

        vao->bind();
        ebo->Draw();
        vao->unbind();

        // LEFT
        translation = glm::vec3(-20.0f, 0.0f, 30.0f);
        //scale = glm::vec3(2.0f, 5.0f, 2.0f);
        scale = glm::vec3(0.25f, 0.25f, 0.25f);
        tmpModel = glm::translate(Model, translation);
        tmpModel = glm::rotate(tmpModel, glm::radians(rotation), rotationZ);
        tmpModel = glm::rotate(tmpModel, glm::radians(rotation), rotationX);
        tmpModel = glm::scale(tmpModel, scale);
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, &tmpModel[0][0]);

        vao->bind();
        ebo->Draw();
        vao->unbind();

        // RIGHT
        translation = glm::vec3(20.0f, 0.0f, 30.0f);
        //scale = glm::vec3(2.0f, 5.0f, 2.0f);
        scale = glm::vec3(0.25f, 0.25f, 0.25f);
        tmpModel = glm::translate(Model, translation);
        tmpModel = glm::rotate(tmpModel, glm::radians(rotation), rotationZ);
        tmpModel = glm::rotate(tmpModel, glm::radians(rotation), rotationY);
        tmpModel = glm::scale(tmpModel, scale);
        glUniformMatrix4fv(modelUniformLoc, 1, GL_FALSE, &tmpModel[0][0]);

        rotation += 1.0f;

        vao->bind();
        ebo->Draw();
        vao->unbind();

        textRenderer->DrawUnicode(L"WELCOME TO\nBRICKPONG ARCADES", -450, 220, 42, textColorRed);
        std::wstring gameText = L"Choose Your game: ";
        if (cursorPosition.x > -20.0f && cursorPosition.x < 20.0f) {
            gameText.append(L"Brickpong");
            *acurrentGame = 0;
        }
        else if (cursorPosition.x < -20.0f) {
            gameText.append(L"Space Invaders");
            *acurrentGame = -1;
        }
        else if (cursorPosition.x > 20.0f) {
            gameText.append(L"Tetris");
            *acurrentGame = 1;
        }
        textRenderer->DrawUnicode(gameText.c_str(), -450, -260, 32, textColorWhite);

        _window->swapBuffers();

        glfwPollEvents();
        if (_window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS || _window->shouldClose() != 0) {
            playGame = false;
        }
    } while ((_window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && _window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS) && _window->shouldClose() == 0);

    delete ebo;
    delete vvbo;
    delete cvbo;
    delete nvbo;
    delete vao;

    delete textRenderer;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete shaderProgram;
    return playGame;
}

bool GameEngine::RunBrickpong(GraphicsEngine* agraphicsEngine, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback, BrickpongGame* abrickpongGame) {
    bool play = true;

    _window->setCursorMode(GLFW_CURSOR_HIDDEN);
    _window->setStickyKeys(GL_TRUE);
    _window->setCursorPosCallback(acursorPositionCallback);
    _window->setKeyCallback(akeyCallback);

    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgram* shaderSemiTransparentProgram = new ShaderProgram();
    ShaderProgram* ballShaderProgram = new ShaderProgram();
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

    Shader* vBallShader = new Shader("shaders/ASSIMP.vert", GL_VERTEX_SHADER);
    Shader* fBallShader = new Shader("shaders/ASSIMP.frag", GL_FRAGMENT_SHADER);
    ballShaderProgram->attachShader(vBallShader);
    ballShaderProgram->attachShader(fBallShader);
    ballShaderProgram->bindFragDataLocation(0, "fragData");
    ballShaderProgram->link();
    delete vBallShader;
    delete fBallShader;

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

    abrickpongGame->CreateGame(agraphicsEngine, ballShaderProgram, shaderProgram, positionAttribLoc, colorAttribLoc, shaderSemiTransparentProgram, positionAttribLoc, colorAttribLoc);

    std::cout << "Points: " << abrickpongGame->GetPoints() << std::endl;

    GLint viewportWidth, viewportHeight;


    double lastTime = 0;
    int nbFrames = 0;

    if (_debugMode > 0) {
        lastTime = glfwGetTime();
        nbFrames = 0;
    }

    Text* textRenderer = new Text(_window, "fonts/Zapfino.ttf", 1);
    GLfloat textColorWhite[4] = {
        1.0, 1.0f, 1.0f, 1.0f,
    };
    GLfloat textColorRed[4] = {
        1.0f, 0.0f, 0.0f, 1.0f
    };
    do {
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
        // Bricks
        abrickpongGame->DrawBricks(&Model, &View, &Projection, MatrixID);
        // Pad
        abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), &Model, &View, &Projection, MatrixID);
        // Ball
        abrickpongGame->GetBall()->Draw(&Model, &View, &Projection);

        std::wstring pointsText = L"Points: ";
        pointsText.append(std::to_wstring(abrickpongGame->GetPoints()));
        textRenderer->DrawUnicode(pointsText.c_str(), 280, 230, 24, textColorWhite);
        std::wstring ballSpeedLevelText = L"Ball speed level: ";
        ballSpeedLevelText.append(std::to_wstring(abrickpongGame->GetBall()->GetLinearVelocityMultiplier()));
        textRenderer->DrawUnicode(ballSpeedLevelText.c_str(), -450, 230, 24, textColorWhite);

        if (abrickpongGame->IsGamePaused()) {
            textRenderer->DrawUnicode(L"GAME PAUSED", -300, -100, 42, textColorRed);
        }

        _window->swapBuffers();

        abrickpongGame->CheckGameResult();
        glfwPollEvents();
        if (_window->getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS || _window->shouldClose() != 0) {
            play = false;
        }
    } while ((_window->getKey(GLFW_KEY_BACKSPACE) != GLFW_PRESS && _window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS) && _window->shouldClose() == 0);

    delete textRenderer;
    delete abrickpongGame;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete shaderProgram;

    return play;
}