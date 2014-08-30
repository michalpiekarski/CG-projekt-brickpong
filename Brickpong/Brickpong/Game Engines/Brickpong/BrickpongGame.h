#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongGame__
#define __Brickpong__Game_Engines__Brickpong__BrickpongGame__

#include <iostream>
#include <vector>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Box2D/Box2D.h>

#include "../../Graphics Engine/Window.h"

struct Cursor {
    float positionX;
    float maxOffset;
    float damping;
};

class BrickpongGame {
private:
    b2World* world;
    b2Body* worldBounds;
    b2Body* ball;
    b2Body* pad;
    std::vector<b2Body*> bricks;
    Cursor cursor;
    std::vector<b2Contact*> contacts;
    b2Vec2 PauseBallVelocity;
    int Points;
    bool gamePaused;
    void CreateWorld(b2Vec2 agravity);
    void DestroyWorld();
    void CreateWorldBounds(float32 worldWidth, float32 worldHeight, b2Vec2 worldCenterOffset);
    void CreateBall();
    void CreatePad();
    void CreateBrick(b2Body* abrick, b2Vec2 pos, b2Vec2 size);
    void CreateManyBricks(b2Vec2 startPos, b2Vec2 endPos, b2Vec2 size, b2Vec2 padding);
    static bool validBallBrickContact(b2Body* A, b2Body* B);

    class BallBrickContactListener : public b2ContactListener {
    private:
        std::vector<b2Contact*>* contacts;
    public:
        BallBrickContactListener(std::vector<b2Contact*>* acontacts);
        void BeginContact(b2Contact* contact);
    };
    BallBrickContactListener* ballBrickContactListener;

    void ConnectContactListenerToWorld();
    void DestroyContactListener();
    void ResetGame();
public:
    BrickpongGame();
    virtual ~BrickpongGame();
    void CreateGame();
    void DestroyGame();
    int GetPoints();
    void StepPhysics(float32 timeStep, int32 velocityIterations, int32 positionIterations);
    void DestroyBricks();
    std::vector<b2Body*> GetBricksList();
    Cursor GetCursor();
    b2Body* GetBall();
    void CursorPositionChanged(GLFWwindow *window, double x, double y);
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods, GLFWcursorposfun currentCursorPosCallback);
    void CheckBallBelowPad();
    void CheckGameWin();
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongGame__) */
