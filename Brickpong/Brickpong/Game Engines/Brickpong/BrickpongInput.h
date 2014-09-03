#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongInput__
#define __Brickpong__Game_Engines__Brickpong__BrickpongInput__

#include <iostream>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>

class BrickpongGame;

class BrickpongInput {
private:
    BrickpongGame* _game;
    b2Vec2 _pauseBallVelocity;
    unsigned short _debugMode;
public:
    BrickpongInput(BrickpongGame* agame);
    BrickpongInput(BrickpongGame* agame, unsigned short adebugMode);
    virtual ~BrickpongInput();
    void CursorPositionChanged(BrickpongGame* agame, GLFWwindow *awindow, double acursorPosX, double acursorPosY);
    void KeyCallback(BrickpongGame* agame, GLFWwindow *awindow, int akey, int ascancode, int aaction, int amods, GLFWcursorposfun acurrentCursorPosCallback);
    b2Vec2 GetPauseBallVelocity();
    void SetBallPauseVelocity(b2Vec2 apauseBallVelocity);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongInput__) */
