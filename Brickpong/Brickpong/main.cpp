#include "main.h"

//    // Comment out for debut output in console
//#define __Brickpong__DEBUG_LOG__

void CreateBuffers(VBO* vVBO, VBO* cVBO, EBO* myEBO) {
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

    vVBO->data(vertex_data, sizeof(vertex_data), GL_STATIC_DRAW);
    cVBO->data(color_data, sizeof(color_data), GL_STATIC_DRAW);
    myEBO->data(index_data, sizeof(index_data), GL_STATIC_DRAW);
}

void Draw(EBO* myEBO) {
    myEBO->bind();
    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_SHORT, NULL);
    myEBO->unbind();
}

void DrawBricks(std::vector<b2Body*> aBricks, EBO* aEBO, glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    for (std::vector<b2Body*>::iterator i = aBricks.begin(); i != aBricks.end(); i++) {
        if ((*i)->IsActive()) {
            b2Vec2 bodyPos = (*i)->GetPosition();
            glm::vec3 translation = glm::vec3(bodyPos.x, bodyPos.y, 0.0f);
            glm::vec3 scale = glm::vec3(0.5f, 0.25f, 0.25f);
            glm::mat4 tmpModel = glm::scale(glm::translate(Model, translation), scale);
            glm::mat4 MVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);
            Draw(aEBO);
        }
    }
}

void DrawPad(Cursor aCursor, EBO* aEBO, glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    glm::mat4 tmpModel = glm::scale(glm::translate(Model, glm::vec3(aCursor.positionX, -7.5f, 0)), glm::vec3(2.0f, 0.25f, 2.0f));
    glm::mat4 MVP = Projection * View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    Draw(aEBO);
}

BrickpongGame* brickpongGame;

void CursorPositionCallback(GLFWwindow* window, double x, double y) {
    brickpongGame->CursorPositionChanged(window, x, y);
}

void KeyboardKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    brickpongGame->KeyCallback(window, key, scancode, action, mods, CursorPositionCallback);
}

int main(void) {
    try {
        brickpongGame = new BrickpongGame();

        Window* window = new Window(960, 540, "Brickpong", false);
        ShaderProgram* shaderProgram;
        Shader* vShader;
        Shader* fShader;

        window->makeContextCurrent();
#ifndef __Brickpong__DEBUG_LOG__
        window->setCursorMode(GLFW_CURSOR_HIDDEN);
#endif
        window->setStickyKeys(GL_TRUE);
        window->setCursorPosCallback(CursorPositionCallback);
        window->setKeyCallback(KeyboardKeyCallback);

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
        glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 Projection = glm::ortho(-8.0f, 8.0f, -8.0f, 1.0f, -1.0f, 1.0f); // Powinna być zachowana taka sama proporcja szerokość:wysokość jaką ma okno (16:9) aby uniknąć zniekształceń

        glm::mat4 tmpModel, tmpMVP;

        VAO* VertexArray = new VAO();
        VertexArray->bind();

        VBO* vVBO = new VBO();
        VBO* cVBO = new VBO();
        EBO* myEBO = new EBO();
        CreateBuffers(vVBO, cVBO, myEBO);

        GLint positionAttribLoc = shaderProgram->getAttributeLoc("position");
        GLint colorAttribLoc = shaderProgram->getAttributeLoc("color");

        vVBO->createVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        cVBO->createVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        brickpongGame->CreateGame();

        std::cout << "Points: " << brickpongGame->GetPoints() << std::endl;

        GLint viewportWidth, viewportHeight;

#ifdef __Brickpong__DEBUG_LOG__
        double lastTime = glfwGetTime();
        int nbFrames = 0;
#endif

        do {
            brickpongGame->StepPhysics(1.0f / 60.0f, 6, 2);
            brickpongGame->CheckBallBelowPad();
            brickpongGame->DestroyBricks();

#ifdef __Brickpong__DEBUG_LOG__
            double currentTime = glfwGetTime();
            nbFrames++;
            if ( currentTime - lastTime >= 1.0 ) {
                std::cout << 1000.0/double(nbFrames) << "ms/frame" << std::endl;
                nbFrames = 0;
                lastTime += 1.0;
            }
#endif

            window->getFrameBufferSize(&viewportWidth, &viewportHeight);
            glViewport(0, 0, viewportWidth, viewportHeight);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Bricks
            DrawBricks(brickpongGame->GetBricksList(), myEBO, Model, View, Projection, MatrixID);

            // Pad
            DrawPad(brickpongGame->GetCursor(), myEBO, Model, View, Projection, MatrixID);

            // Ball
            b2Body* tmpBall = brickpongGame->GetBall();
            glm::vec3 tmpBallPosition = glm::vec3(tmpBall->GetPosition().x, tmpBall->GetPosition().y, 0.0f);
            tmpModel = glm::scale(glm::translate(Model, tmpBallPosition), glm::vec3(0.25f, 0.25f, 0.25f));

            tmpMVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

            Draw(myEBO);

            window->swapBuffers();

            brickpongGame->CheckGameWin();
            glfwPollEvents();
        } while (window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS && window->shouldClose() == 0);

        delete brickpongGame;
        /*DestroyGame();
        delete bbContactListener;*/

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        delete myEBO;
        delete vVBO;
        delete cVBO;

        delete VertexArray;

        delete shaderProgram;
        delete window;

        return 0;
    }
    catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
