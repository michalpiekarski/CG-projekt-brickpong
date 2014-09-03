#include "GameEngine.h"

GameEngine::GameEngine(Window* awindow) {
    _window = awindow;
}

GameEngine::~GameEngine() {

}

void GameEngine::RunBrickpong(GraphicsEngine* agraphicsEngine, GLFWcursorposfun acursorPositionCallback, GLFWkeyfun akeyCallback, BrickpongGame* abrickpongGame) {
    ShaderProgram* shaderProgram;
    Shader* vShader;
    Shader* fShader;

    _window->makeContextCurrent();
    _window->setCursorMode(GLFW_CURSOR_HIDDEN);
    _window->setStickyKeys(GL_TRUE);
    _window->setCursorPosCallback(acursorPositionCallback);
    _window->setKeyCallback(akeyCallback);

    shaderProgram = new ShaderProgram();
    vShader = new Shader("shaders/Simple.vert", GL_VERTEX_SHADER);
    fShader = new Shader("shaders/Simple.frag", GL_FRAGMENT_SHADER);

    shaderProgram->attachShader(vShader);
    shaderProgram->attachShader(fShader);

    shaderProgram->bindFragDataLocation(0, "fragData");

    shaderProgram->link();
    shaderProgram->use();

    delete vShader;
    delete fShader;

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint MatrixID = shaderProgram->getUniformLoc("MVP");

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 View = agraphicsEngine->ZoomIn();
    glm::mat4 Projection = agraphicsEngine->ChangeToOrtographic();

    glm::mat4 tmpModel, tmpMVP;

    VAO* VertexArray = new VAO();
    VertexArray->bind();

    GLfloat vertex_data[8][3] = {
            {-1.0f, -1.0f, -1.0f, },
            {-1.0f, -1.0f, +1.0f, },
            {-1.0f, +1.0f, +1.0f, },
            {+1.0f, +1.0f, -1.0f, },
            {-1.0f, +1.0f, -1.0f, },
            {+1.0f, -1.0f, +1.0f, },
            {+1.0f, -1.0f, -1.0f, },
            {+1.0f, +1.0f, +1.0f, },
    };
    VBO* vVBO = new VBO(vertex_data, 8, GL_STATIC_DRAW);
    GLfloat color_data[8][3] = {
            {0.583f, 0.771f, 0.014f, },
            {0.609f, 0.115f, 0.436f, },
            {0.327f, 0.483f, 0.844f, },
            {0.822f, 0.569f, 0.201f, },
            {0.435f, 0.602f, 0.223f, },
            {0.310f, 0.747f, 0.185f, },
            {0.597f, 0.770f, 0.761f, },
            {0.559f, 0.436f, 0.730f, },
    };
    VBO* cVBO = new VBO(color_data, 8, GL_STATIC_DRAW);
    GLushort index_data[12][3] = {
            {0, 1, 2, },
            {3, 0, 4, },
            {5, 0, 6, },
            {3, 6, 0, },
            {0, 2, 4, },
            {5, 1, 0, },
            {2, 1, 5, },
            {7, 6, 3, },
            {6, 7, 5, },
            {7, 3, 4, },
            {7, 4, 2, },
            {7, 2, 5, },
    };
    EBO* myEBO = new EBO(index_data, 12, GL_STATIC_DRAW);

    GLint positionAttribLoc = shaderProgram->getAttributeLoc("position");
    GLint colorAttribLoc = shaderProgram->getAttributeLoc("color");

    vVBO->createVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    cVBO->createVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    abrickpongGame->CreateGame();

    std::cout << "Points: " << abrickpongGame->GetPoints() << std::endl;

    GLint viewportWidth, viewportHeight;

#ifdef __Brickpong__DEBUG_LOG__
    double lastTime = glfwGetTime();
    int nbFrames = 0;
#endif

    do {
        View = agraphicsEngine->ChangeZoomLevel(_window, View);
        Projection = agraphicsEngine->ChangeProjection();

        abrickpongGame->GetWorld()->Step();
        abrickpongGame->DestroyBricks();

#ifdef __Brickpong__DEBUG_LOG__
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << 1000.0 / double(nbFrames) << "ms/frame" << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
#endif

        _window->getFrameBufferSize(&viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (agraphicsEngine->IsZoomed()) {
            // Bricks
            abrickpongGame->DrawBricks(myEBO, Model, View, Projection, MatrixID);

            // Pad
            abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), myEBO, Model, View, Projection, MatrixID);

            // Ball
            abrickpongGame->GetBall()->Draw(myEBO, Model, View, Projection, MatrixID);
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
                Model = glm::rotate(Model, i, glm::vec3(0.0f, 1.0f, 0.0f));
                Model = glm::translate(Model, sceneOffset);
                // Bricks
                abrickpongGame->DrawBricks(myEBO, Model, View, Projection, MatrixID);

                // Pad
                abrickpongGame->GetPad()->Draw(abrickpongGame->GetCursor(), myEBO, Model, View, Projection, MatrixID);

                // Ball
                abrickpongGame->GetBall()->Draw(myEBO, Model, View, Projection, MatrixID);

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

    delete myEBO;
    delete vVBO;
    delete cVBO;

    delete VertexArray;

    delete shaderProgram;
}