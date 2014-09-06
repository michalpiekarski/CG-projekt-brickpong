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

bool GameEngine::Run(int* acurrentGame, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback) {
    bool playGame = true;

    _window->setCursorMode(GLFW_CURSOR_HIDDEN);
    _window->setStickyKeys(GL_TRUE);
    _window->setCursorPosCallback(acursorPositionCallback);
    _window->setKeyCallback(akeyCallback);

    ShaderProgram* shaderProgram = new ShaderProgram();
    Shader* vShader = new Shader("shaders/Simple.vert", GL_VERTEX_SHADER);
    Shader* fShader = new Shader("shaders/Simple.frag", GL_FRAGMENT_SHADER);
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

    GLuint MatrixID = shaderProgram->getUniformLoc("MVP");

    glm::mat4 Model = glm::mat4(1.0f);
    glm::vec2 cursorPosition = _window->getCursorPositionInWorldSpace(60.0f, 2.0f, glm::vec2(0.0f, 0.0f));
    glm::vec3 viewTarget = glm::vec3(cursorPosition.x, cursorPosition.y-2.0f, glm::abs(cursorPosition.x));
    glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 1.0f, 30.0f), viewTarget, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Projection = glm::perspective(120.0f, 16.0f / 9.0f, 0.01f, 10000.0f);

    glm::mat4 tmpModel, tmpMVP;

    GLint positionAttribLoc = shaderProgram->getAttributeLoc("position");
    GLint colorAttribLoc = shaderProgram->getAttributeLoc("color");

    shaderProgram->use();
    VAO* vao = new VAO();
    vao->bind();

    GLfloat vertex_data[9][3] = {
            {-1.0f, -1.0f, -1.0f, }, // 0-E
            {-1.0f, -1.0f, +1.0f, }, // 1-H
            {-1.0f, +1.0f, +1.0f, }, // 2-D
            {+1.0f, +1.0f, -1.0f, }, // 3-B
            {-1.0f, +1.0f, -1.0f, }, // 4-A
            {+1.0f, -1.0f, +1.0f, }, // 5-G
            {+1.0f, -1.0f, -1.0f, }, // 6-F
            {+1.0f, +1.0f, +1.0f, }, // 7-C
            {+0.0f, +0.0f, +1.0f, }, // 8-I
    };
    VBO* vvbo = new VBO(vertex_data, 9, GL_STATIC_DRAW);
    GLfloat color_data[9][3] = {
            {0.0f, 0.0f, 1.0f, }, // 0-E
            {0.0f, 1.0f, 0.0f, }, // 1-H
            {0.0f, 1.0f, 0.0f, }, // 2-D
            {1.0f, 0.0f, 0.0f, }, // 3-B
            {0.0f, 0.0f, 1.0f, }, // 4-A
            {0.0f, 1.0f, 0.0f, }, // 5-G
            {1.0f, 0.0f, 0.0f, }, // 6-F
            {0.0f, 1.0f, 0.0f, }, // 7-C
            {0.0f, 0.0f, 0.0f, }, // 8-I
    };
    VBO* cvbo = new VBO(color_data, 9, GL_STATIC_DRAW);
    GLushort index_data[14][3] = {
            {0, 1, 2, }, // EHD - left
            {0, 2, 4, }, // EDA - left
            {3, 0, 4, }, // BEA - back
            {3, 6, 0, }, // BFE - back
            {7, 6, 3, }, // CFB - right
            {6, 7, 5, }, // FCG - right
            {5, 0, 6, }, // GEF - bottom
            {5, 1, 0, }, // GHE - bottom
            {7, 3, 4, }, // CBA - top
            {7, 4, 2, }, // CAD - top
            //{7, 2, 5, }, // CDG - front
            //{2, 1, 5, }, // DHG - front
            {8, 2, 1, }, // IDH - front
            {8, 7, 2, }, // ICD - front
            {8, 5, 7, }, // IGC - front
            {8, 1, 5, }, // IHG - front
    };
    EBO* ebo = new EBO(index_data, 14, GL_STATIC_DRAW);

    vvbo->createVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    cvbo->createVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

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
        cursorPosition = _window->getCursorPositionInWorldSpace(60.0f, 2.0f, glm::vec2(0.0f, 0.0f));
        viewTarget = glm::vec3(cursorPosition.x, cursorPosition.y-2.0f, glm::abs(cursorPosition.x));
        View = glm::lookAt(glm::vec3(0.0f, 1.0f, 30.0f), viewTarget, glm::vec3(0.0f, 1.0f,0.0f));

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

        shaderProgram->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 translation, scale;
        glm::mat4 tmpModel, MVP;

        // FRONT
        translation = glm::vec3(0.0f, 0.0f, 10.0f);
        scale = glm::vec3(2.0f, 5.0f, 2.0f);
        tmpModel = glm::scale(glm::translate(Model, translation), scale);
        MVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        vao->bind();
        ebo->Draw();
        vao->unbind();

        // LEFT
        translation = glm::vec3(-20.0f, 0.0f, 30.0f);
        scale = glm::vec3(2.0f, 5.0f, 2.0f);
        tmpModel = glm::scale(glm::translate(Model, translation), scale);
        MVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        vao->bind();
        ebo->Draw();
        vao->unbind();

        // RIGHT
        translation = glm::vec3(20.0f, 0.0f, 30.0f);
        scale = glm::vec3(2.0f, 5.0f, 2.0f);
        tmpModel = glm::scale(glm::translate(Model, translation), scale);
        MVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        vao->bind();
        ebo->Draw();
        vao->unbind();

        // BACK
        translation = glm::vec3(0.0f, 0.0f, 50.0f);
        scale = glm::vec3(2.0f, 5.0f, 2.0f);
        tmpModel = glm::scale(glm::translate(Model, translation), scale);
        MVP = Projection * View * tmpModel;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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

    vao->unbind();
    delete ebo;
    delete vvbo;
    delete cvbo;
    delete vao;

    delete textRenderer;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete shaderProgram;
    return playGame;
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
        abrickpongGame->DrawBricks(Model, View, Projection, MatrixID);
        // Pad
        abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), Model, View, Projection, MatrixID);
        // Ball
        abrickpongGame->GetBall()->Draw(Model, View, Projection, MatrixID);

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
    } while ((_window->getKey(GLFW_KEY_BACKSPACE) != GLFW_PRESS && _window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS) && _window->shouldClose() == 0);

    delete textRenderer;
    delete abrickpongGame;

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    delete shaderProgram;
}