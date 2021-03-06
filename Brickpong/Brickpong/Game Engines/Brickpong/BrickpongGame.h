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

#include "../../Graphics Engine/GraphicsEngine.h"
#include "BrickpongWorld.h"
#include "BrickpongWorldBounds.h"
#include "BrickpongBall.h"
#include "BrickpongPad.h"
#include "BrickpongBrick.h"
#include "BrickpongInput.h"
#include "BrickpongBrickLayout.h"

struct Cursor {
    float positionX;
    float maxOffset;
    float damping;
};

class BrickpongGame {
    class BallBrickContactListener : public b2ContactListener {
    private:
        std::vector<b2Contact*>* contacts;
    public:
        BallBrickContactListener(std::vector<b2Contact*>* acontacts);
        void BeginContact(b2Contact* contact);
    };
private:
    BrickpongWorld* _world;
    BrickpongWorldBounds* _worldBounds;
    BrickpongBall* _ball;
    BrickpongPad* _pad;
    std::vector<BrickpongBrick*> _bricks;
    BrickpongInput* _input;
    Cursor _cursor;
    std::vector<b2Contact*> _contacts;
    b2Vec2 _pauseBallVelocity;
    int _points;
    bool _gamePaused;
    BallBrickContactListener* _ballBrickContactListener;
    unsigned short _debugMode;
    void CreateBricksFromGrid(b2Vec2 astartPos, b2Vec2 aendPos, float awidth, float aheight, b2Vec2 apadding, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc);
    void CreateBricksFromLayout(std::vector<BrickpongBrickLayout*> alayout, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc);
    static bool validBallBrickContact(b2Body* A, b2Body* B);
    void ConnectContactListenerToWorld();
    void DestroyContactListener();
    void CheckGameOver();
    void CheckGameWin();
public:
    BrickpongGame();
    BrickpongGame(unsigned short adebugMode);
    virtual ~BrickpongGame();
    void CreateGame(GraphicsEngine* agraphicsEngine, ShaderProgram* aballShaderProgram, ShaderProgram* apadShaderProgram, GLint apadPositionAttribLoc, GLint apadColorAttribLoc, ShaderProgram* abrickShaderProgram, GLint abrickPositionAttribLoc, GLint abrickColorAttribLoc);
    void DestroyGame();
    int GetPoints();
    void DestroyBricks();
    std::vector<BrickpongBrick*> GetBricksList();
    Cursor* GetCursor();
    BrickpongBall* GetBall();
    void CheckGameResult();
    BrickpongPad* GetPad();
    bool IsGamePaused();
    void SetGamePaused(bool agamePaused);
    void ResetGame();
    BrickpongWorld* GetWorld();
    BrickpongInput* GetInput();
    void DrawBricks(glm::mat4* Model, glm::mat4* View, glm::mat4* Projection, GLuint MVP_ID);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongGame__) */
