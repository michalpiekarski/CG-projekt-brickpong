// Include Sysytem Headers
#include <iostream>

// Include GLM
#include <glm/gtc/matrix_transform.hpp>

// Include Custom Headers
#include "BrickpongException.h"
#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

//    // Comment out for debut output in console
//#define __Brickpong__DEBUG_LOG__

float CursorX = 0.0f;
float CurserOffset = 150.0f;
float CursorDamping = 10.0f;

glm::vec3 BallPosition = glm::vec3(1.0f, -6.0f, 0);
glm::vec3 BallVelocity = glm::vec3(0.05f, 0.1f, 0);
glm::vec3 PauseBallVelocity = glm::vec3(0, 0, 0);

int Points = 0;
bool bricks[500];

void CreateBuffers(VBO* vVBO, VBO* cVBO, EBO* myEBO) {
    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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

    // One color for each vertex. They were generated randomly.
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
        {0, 1, 2,},
        {3, 0, 4,},
        {5, 0, 6,},
        {3, 6, 0,},
        {0, 2, 4,},
        {5, 1, 0,},
        {2, 1, 5,},
        {7, 6, 3,},
        {6, 7, 5,},
        {7, 3, 4,},
        {7, 4, 2,},
        {7, 2, 5,},
    };

    vVBO->data(vertex_data, sizeof(vertex_data), GL_STATIC_DRAW);
    cVBO->data(color_data, sizeof(color_data), GL_STATIC_DRAW);
    myEBO->data(index_data, sizeof(index_data), GL_STATIC_DRAW);
}

void Draw(VBO* vVBO, VBO* cVBO, EBO* myEBO) {
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vVBO->getID());
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, cVBO->getID());
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
        );

    myEBO->bind();
    // Draw the triangle !
    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, NULL);


    myEBO->unbind();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void cursorPositionChanged(GLFWwindow *window, double x, double y) {
    int windowWidth;
    glfwGetFramebufferSize(window, &windowWidth, NULL);
    CursorX = glm::clamp(float(-(x - windowWidth / 2.0f)), -CurserOffset, CurserOffset) / CursorDamping;
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Cursor x position: " << CursorX << std::endl;
#endif
}

void ResetGame() {
    BallPosition = glm::vec3(1.0f, -6.0f, 0);
    BallVelocity = glm::vec3(0.05f, 0.1f, 0);
    for (int i = 0; i < 500; i++) {
        bricks[i] = false;
    }
    Points = 0;
    std::cout << "Points: " << Points <<std::endl;
}
bool gamePaused = false;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE && key == GLFW_KEY_SPACE) {
        glm::vec3 tmp = BallVelocity;
        tmp = BallVelocity;
        BallVelocity = PauseBallVelocity;
        PauseBallVelocity = tmp;
        if (!gamePaused) {
            gamePaused = true;
            glfwSetCursorPosCallback(window, NULL);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#ifdef __Brickpong__DEBUG_LOG__
            std::cout << "Game Paused" << std::endl;
#endif
        }
        else {
            gamePaused = false;
            glfwSetCursorPosCallback(window, cursorPositionChanged);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#ifdef __Brickpong__DEBUG_LOG__
            std::cout << "Game Resumed" << std::endl;
#endif
        }
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
            CursorX += 1.0f;
        }
        else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
            CursorX -= 1.0f;
        }
        if (key == GLFW_KEY_R) {
            ResetGame();
        }
    }
}

void CheckBallBoundsCol() {
    // Horizontal
    if (BallPosition.x < -14.0f || BallPosition.x > 14.0f) {
        BallVelocity.x = -BallVelocity.x;
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << BallPosition.x << "; " << BallPosition.y << ")" << std::endl;
#endif
    }
    // Top
    else if (BallPosition.y > 8.0f) {
        BallVelocity.y = -BallVelocity.y;
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << BallPosition.x << "; " << BallPosition.y << ")" << std::endl;
#endif
    }
    // Bottom
    else if (BallPosition.y < -8.0f) {
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << BallPosition.x << "; " << BallPosition.y << ")" << std::endl;
#endif
        std::cout << "##GAME OVER ##" << std::endl << std::endl;
        ResetGame();
    }
}

void CheckBallPadCol() {
    if (BallPosition.y <= -6.2f && (BallPosition.x >= CursorX - 2.0f && BallPosition.x <= CursorX + 2.0f)) {
        if (BallPosition.x > CursorX - 0.15f && BallPosition.x < CursorX + 0.15f) {
            BallVelocity.x -= 0.025f;
            BallVelocity.y = glm::clamp(BallVelocity.y + 0.025f, -0.3f, 0.3f);
        }
        else {
            BallVelocity.x = glm::clamp(BallVelocity.x + 0.025f, -0.3f, 0.3f);
        }
        if ((BallVelocity.x < 0 && BallPosition.x > CursorX + 0.8f) || (BallVelocity.x > 0 && BallPosition.x < CursorX - 0.8f)) {
            BallVelocity.x = -BallVelocity.x;
        }
        BallVelocity.y = -BallVelocity.y;
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Pad collision at: (" << BallPosition.x << "; " << BallPosition.y << ")" << std::endl;
#endif
    }
}

bool CheckBallBrickCol(float brickX, float brickY) {
    // No collision
    // top || right || bottom || left
    if (BallPosition.y - 0.3f > brickY + 0.3f || BallPosition.x + 0.3f < brickX - 0.6f || BallPosition.y + 0.3f < brickY - 0.3f || BallPosition.x - 0.3f > brickX + 0.6f) {
        return false;
    }
    // Collision
    if (BallPosition.x < brickX - 0.65f || BallPosition.x > brickX + 0.65f) {
        BallVelocity.x = -BallVelocity.x;
    }
    if (BallPosition.y < brickY - 0.4f || BallPosition.y > brickY + 0.4f) {
        BallVelocity.y = -BallVelocity.y;
    }
    ++Points;
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Points: " << Points << std::endl;
#endif
    return true;
}

void CheckGameWin() {
    if (Points == 70) {
        std::cout << "=== YOU WON! ===" << std::endl << std::endl;
        ResetGame();
    }
}

int main(void) {
    try {
        Window* window = new Window(960, 540, "Brickpong", false);
        ShaderProgram* shaderProgram;
        Shader* vShader;
        Shader* fShader;

        window->makeContextCurrent();
        window->setCursorMode(GLFW_CURSOR_HIDDEN);
        window->setStickyKeys(GL_TRUE);
        window->setCursorPosCallback(cursorPositionChanged);
        window->setKeyCallback(KeyCallback);

        shaderProgram = new ShaderProgram();
        vShader = new Shader("shaders/TransformVertexShader.vert", GL_VERTEX_SHADER);
        fShader = new Shader("shaders/ColorFragmentShader.frag", GL_FRAGMENT_SHADER);

        shaderProgram->attachShader(vShader);
        shaderProgram->attachShader(fShader);

        shaderProgram->bindFragDataLocation(0, "fragData");

        shaderProgram->link();
        shaderProgram->use();

        delete vShader;
        delete fShader;

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        GLuint MatrixID = shaderProgram->getUniformLoc("MVP");

        glm::mat4 Model = glm::mat4(1.0f);
        glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, -20), // Camera is at (0,0,-20), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );
        glm::mat4 Projection = glm::perspective(
            45.0f, // 45° Field of View
            16.0f / 9.0f, // 16:9 ratio
            0.1f, 100.0f // display range : 0.1 unit <-> 100 units
            );

        //        // Our ModelViewProjection : multiplication of our 3 matrices
        //	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

        glm::mat4 tmpModel, tmpMVP;

        VAO* VertexArray = new VAO();
        VertexArray->bind();

        VBO* vVBO = new VBO();
        VBO* cVBO = new VBO();
        EBO* myEBO = new EBO();
        CreateBuffers(vVBO, cVBO, myEBO);

        for (int i = 0; i < 500; i++) {
            bricks[i] = false;
        }

        std::cout << "Points: " << Points << std::endl;

        do {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Bricks
            int brick_i = 0;
            for (float i = -12.0f; i <= 12.0f; i += 2.0f) {
                for (float j = 0.0f; j <= 7.0f; j += 1.0f) {
                    if (!bricks[brick_i]) {
                        if (!CheckBallBrickCol(i, j)) {
                            // Send our transformation to the currently bound shader,
                            // in the "MVP" uniform
                            tmpModel = glm::scale(glm::translate(Model, glm::vec3(i, j, 0)), glm::vec3(1.0f, 0.5f, 0.5f));
                            tmpMVP = Projection * View * tmpModel;
                            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

                            Draw(vVBO, cVBO, myEBO);
                        }
                        else {
#ifdef __Brickpong__DEBUG_LOG__
                            std::cout << "Brick nr. " << brick_i << " destroyed" << std::endl;
#endif
                            bricks[brick_i] = true;
                        }
                    }
                    ++brick_i;
                }
            }

            CheckGameWin();

            // Pad
            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform
            tmpModel = glm::scale(glm::translate(Model, glm::vec3(CursorX, -7.0f, 0)), glm::vec3(2.0f, 0.25f, 2.0f));
            tmpMVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

            Draw(vVBO, cVBO, myEBO);

            // Ball
            // Send our transformation to the currently bound shader,
            // in the "MVP" uniform
            tmpModel = glm::scale(glm::translate(Model, BallPosition), glm::vec3(0.25f, 0.25f, 0.25f));
            BallPosition += BallVelocity;
            CheckBallBoundsCol();
            CheckBallPadCol();
            tmpMVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

            Draw(vVBO, cVBO, myEBO);

            // Swap buffers
            window->swapBuffers();
            glfwPollEvents();
        } // Check if the ESC key was pressed or the window was closed
        while (window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS && window->shouldClose() == 0);

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

