#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongPad__
#define __Brickpong__Game_Engines__Brickpong__BrickpongPad__

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

struct Cursor;

class BrickpongPad {
private:
    b2Body* _body;
    float _width;
    float _height;
    ShaderProgram* _shaderProgram;
    VAO* _vao;
    EBO* _ebo;
public:
    BrickpongPad(b2World* aworld, float awidth, float aheight, float acursorPositionX, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc);
    virtual ~BrickpongPad();
    b2Vec2 GetPosition();
    float GetAngle();
    void SetTransform(b2Vec2 aposition, float aangle);
    void Draw(Cursor* aCursor, glm::mat4* Model, glm::mat4* View, glm::mat4* Projection, GLuint MVP_ID);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongPad__) */
