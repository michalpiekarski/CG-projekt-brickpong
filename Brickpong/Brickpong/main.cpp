#include "main.h"

    //    // Comment out for debut output in console
    //#define __Brickpong__DEBUG_LOG__

b2World* world;
b2Body* ball;
b2Body* pad;
struct Brick {
    b2Body* body;
    bool destroyed;
};
std::list<Brick> bricks;
struct Cursor {
    float positionX = 0.0f;
    float maxOffset = 9.0f;
    float damping = 0.5f;
} cursor;

void CreateWorld(b2Vec2 agravity) {
    world = new b2World(agravity);
}

void DestroyWorld(){
    delete world;
}

void CreateBall() {
    b2BodyDef ballBDef;
    ballBDef.type = b2_dynamicBody;
    ballBDef.position.Set(1.0f, -5.0f);
    ballBDef.linearVelocity.Set(2.0f, 4.0f);
    ballBDef.gravityScale = 0.0f;
    ballBDef.linearDamping = 0.0f;
    ballBDef.bullet = true;
    ball = world->CreateBody(&ballBDef);
    b2CircleShape ballShape;
    ballShape.m_radius = 0.25f;
    b2FixtureDef ballFDef;
    ballFDef.shape = &ballShape;
    ballFDef.density = 1.0f;
    ballFDef.friction = 0.5f;
    ballFDef.restitution = 1.0f;
    ball->CreateFixture(&ballFDef);
}

void CreatePad() {
    b2BodyDef padBDef;
    padBDef.type = b2_kinematicBody;
    padBDef.position.Set(cursor.positionX, -7.0f);
    pad = world->CreateBody(&padBDef);
    b2PolygonShape padShape;
    padShape.SetAsBox(2.0f, 0.5f);
    pad->CreateFixture(&padShape, 0.0f);
}

void CreateBrick(Brick* abrick, b2Vec2 pos, b2Vec2 size) {
    b2BodyDef brickBDef;
    brickBDef.type = b2_staticBody;
    brickBDef.position.Set(pos.x, pos.y);
    abrick->body = world->CreateBody(&brickBDef);
    b2PolygonShape brickShape;
    brickShape.SetAsBox(size.x/2.0f, size.y/2.0f);
    abrick->body->CreateFixture(&brickShape, 0.0f);
    abrick->destroyed = false;
}

void CreateManyBricks(b2Vec2 startPos, b2Vec2 endPos, b2Vec2 size, b2Vec2 padding) {
    b2BodyDef brickBDef;
    brickBDef.type = b2_staticBody;
    b2PolygonShape brickShape;
    brickShape.SetAsBox(size.x/2.0f, size.y/2.0f);
    for (float32 x = startPos.x; x <= endPos.x; x+=size.x+padding.x) {
        for (float32 y = startPos.y; y <= endPos.y; y+=size.y+padding.y) {
            brickBDef.position.Set(x, y);
            b2Body* brickBody = world->CreateBody(&brickBDef);
            brickBody->CreateFixture(&brickShape, 0.0f);
            Brick brick;
            brick.body = brickBody;
            brick.destroyed = false;
            bricks.push_back(brick);
        }
    }
}

void CreateGame() {
    CreateWorld(b2Vec2(0.0f, -10.0f));
    CreateBall();
    CreatePad();
    CreateManyBricks(b2Vec2(-6.0f, -3.0f), b2Vec2(6.0f, 0.0f), b2Vec2(2.0f, 1.0f), b2Vec2(0.0f, 0.0f));
}

void DestroyGame() {
    DestroyWorld();
}

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

void Draw(EBO* myEBO) {
    myEBO->bind();
    glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_SHORT, NULL);
    myEBO->unbind();
}

void cursorPositionChanged(GLFWwindow *window, double x, double y) {
    int windowWidth;
    glfwGetFramebufferSize(window, &windowWidth, NULL);
    int halfWindowWidth = windowWidth / 2.0f;
    float cursorXOffsetFromMiddle = (x - halfWindowWidth) / (halfWindowWidth/cursor.maxOffset) * cursor.damping;
    cursor.positionX = glm::clamp(cursorXOffsetFromMiddle, -cursor.maxOffset, cursor.maxOffset);
    pad->SetTransform(b2Vec2(cursor.positionX, pad->GetPosition().y), 0.0f);
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Cursor x position: " << cursor.positionX << std::endl;
#endif
}

b2Vec2 PauseBallVelocity = b2Vec2(0.0f, 0.0f);
int Points = 0;
bool gamePaused = false;

void ResetGame() {
    ball->SetTransform(b2Vec2(1.0f, -6.0f), 0.0f);
    ball->SetLinearVelocity(b2Vec2(2.0f, 4.0f));
    for (std::list<Brick>::iterator i = bricks.begin(); i != bricks.end(); i++) {
        (*i).destroyed = false;
    }
    Points = 0;
    std::cout << "Points: " << Points <<std::endl;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE && key == GLFW_KEY_SPACE) {
        b2Vec2 tmp = ball->GetLinearVelocity();
        ball->SetLinearVelocity(PauseBallVelocity);
        PauseBallVelocity = tmp;
        if (!gamePaused) {
            gamePaused = true;
            glfwSetCursorPosCallback(window, NULL);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif
            std::cout << "Ball position: " << ball->GetPosition().x << "; " << ball->GetPosition().y << " | ";
            std::cout << "Pad position: " << pad->GetPosition().x << "; " << pad->GetPosition().y << std::endl;
#ifdef __Brickpong__DEBUG_LOG__
            std::cout << "Game Paused" << std::endl;
#endif
        }
        else {
            gamePaused = false;
            glfwSetCursorPosCallback(window, cursorPositionChanged);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
#ifdef __Brickpong__DEBUG_LOG__
            std::cout << "Game Resumed" << std::endl;
#endif
        }
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
            cursor.positionX += 1.0f;
        }
        else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
            cursor.positionX -= 1.0f;
        }
        if (key == GLFW_KEY_R) {
            ResetGame();
        }
    }
}

void CheckBallBoundsCol() {
        // Horizontal
    if (ball->GetPosition().x < -8.0f || ball->GetPosition().x > 8.0f) {
        ball->SetLinearVelocity(b2Vec2(-ball->GetLinearVelocity().x, ball->GetLinearVelocity().y));
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << ball->GetPosition().x << "; " << ball->GetPosition().y << ")" << std::endl;
#endif
    }
        // Top
    else if (ball->GetPosition().y > 1.0f) {
        ball->SetLinearVelocity(b2Vec2(ball->GetLinearVelocity().x, -ball->GetLinearVelocity().y));
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << ball->GetPosition().x << "; " << ball->GetPosition().y << ")" << std::endl;
#endif
    }
        // Bottom
    else if (ball->GetPosition().y < -7.5f) {
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Wall collision at: (" << ball->GetPosition().x << "; " << ball->GetPosition().y << ")" << std::endl;
#endif
        std::cout << "##GAME OVER ##" << std::endl << std::endl;
        ResetGame();
    }
}

    // TODO: Zamienić stare funkcje obsługi kolizji na nowe, bazujące na kolizjach wykrywanych przez bibliotekę Box2D
/*
void CheckBallPadCol() {
    if (ball->GetPosition().y <= -6.2f && (ball->GetPosition().x >= cursor.positionX - 2.0f && ball->GetPosition().x <= cursor.positionX + 2.0f)) {
        if (ball->GetPosition().x > cursor.positionX - 0.15f && ball->GetPosition().x < cursor.positionX + 0.15f) {
            ball->SetLinearVelocity(b2Vec2(ball->GetLinearVelocity().x-0.025f,
                                           glm::clamp(ball->GetLinearVelocity().y+0.025f, -0.3f, 0.3f))
                                    );
        }
        else {
            ball->SetLinearVelocity(b2Vec2(glm::clamp(ball->GetLinearVelocity().x+0.025f, -0.3f, 0.3f),
                                           ball->GetLinearVelocity().y)
                                    );
        }
        if ((ball->GetLinearVelocity().x < 0 && ball->GetPosition().x > cursor.positionX + 0.8f) || (ball->GetLinearVelocity().x > 0 && ball->GetPosition().x < cursor.positionX - 0.8f)) {
            ball->SetLinearVelocity(b2Vec2(-ball->GetLinearVelocity().x, ball->GetLinearVelocity().y));
        }
        ball->SetLinearVelocity(b2Vec2(ball->GetLinearVelocity().x, -ball->GetLinearVelocity().y));
#ifdef __Brickpong__DEBUG_LOG__
        std::cout << "Pad collision at: (" << ball->GetPosition().x << "; " << ball->GetPosition().y << ")" << std::endl;
#endif
    }
}

bool CheckBallBrickCol(float brickX, float brickY) {
        // No collision
        // top || right || bottom || left
    if (ball->GetPosition().y - 0.3f > brickY + 0.3f || ball->GetPosition().x + 0.3f < brickX - 0.6f || ball->GetPosition().y + 0.3f < brickY - 0.3f || ball->GetPosition().x - 0.3f > brickX + 0.6f) {
        return false;
    }
        // Collision
    if (ball->GetPosition().x < brickX - 0.65f || ball->GetPosition().x > brickX + 0.65f) {
        ball->SetLinearVelocity(b2Vec2(-ball->GetLinearVelocity().x, ball->GetLinearVelocity().y));
    }
    if (ball->GetPosition().y < brickY - 0.4f || ball->GetPosition().y > brickY + 0.4f) {
        ball->SetLinearVelocity(b2Vec2(ball->GetLinearVelocity().x, -ball->GetLinearVelocity().y));
    }
    ++Points;
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Points: " << Points << std::endl;
#endif
    return true;
}
*/

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
#ifndef __Brickpong__DEBUG_LOG__
        window->setCursorMode(GLFW_CURSOR_HIDDEN);
#endif
        window->setStickyKeys(GL_TRUE);
        window->setCursorPosCallback(cursorPositionChanged);
        window->setKeyCallback(KeyCallback);

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

        CreateGame();

        std::cout << "Points: " << Points << std::endl;

        GLint viewportWidth, viewportHeight;

#ifdef __Brickpong__DEBUG_LOG__
        double lastTime = glfwGetTime();
        int nbFrames = 0;
#endif

        do{
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
            int brickIndex = 0;
            for (std::list<Brick>::iterator i = bricks.begin(); i != bricks.end(); i++) {
                if(!(*i).destroyed) {
                        // TODO: Zaimplementować reakcję na kolizje piłki z kolckami
//                    if(!BallBrickCollisionDetected){
                        tmpModel = glm::scale(glm::translate(Model,
                                                             glm::vec3((*i).body->GetPosition().x,
                                                                       (*i).body->GetPosition().y, 0.0f)
                                                             ),
                                              glm::vec3(1.0f, 0.5f, 0.5f)
                                              );
                        tmpMVP = Projection * View * tmpModel;
                        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);
                        Draw(myEBO);
//                    }
//                    else {
//#ifdef __Brickpong__DEBUG_LOG__
//                        std::cout << "Brick nr. " << brickIndex << " destroyed" << std::endl;
//#endif
//                        (*i).destroyed = true;
//                    }
                }
                ++brickIndex;
            }

            CheckGameWin();

                // Pad
            tmpModel = glm::scale(glm::translate(Model, glm::vec3(cursor.positionX, -7.0f, 0)), glm::vec3(2.0f, 0.5f, 2.0f));
            tmpMVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

            Draw(myEBO);

                // Ball
            glm::vec3 tmpBallPosition = glm::vec3(ball->GetPosition().x, ball->GetPosition().y, 0.0f);
            tmpModel = glm::scale(glm::translate(Model, tmpBallPosition), glm::vec3(0.25f, 0.25f, 0.25f));

            world->Step(1.0f/60.0f, 6, 2);

            CheckBallBoundsCol();
            tmpMVP = Projection * View * tmpModel;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &tmpMVP[0][0]);

            Draw(myEBO);

            window->swapBuffers();
            glfwPollEvents();
        } while (window->getKey(GLFW_KEY_ESCAPE) != GLFW_PRESS && window->shouldClose() == 0);

        DestroyGame();

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
