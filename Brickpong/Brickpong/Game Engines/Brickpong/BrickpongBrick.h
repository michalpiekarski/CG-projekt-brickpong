#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongBrick__
#define __Brickpong__Game_Engines__Brickpong__BrickpongBrick__

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

class BrickpongBrick {
private:
    b2Body* _body;
    float _width;
    float _height;
    ShaderProgram* _shaderProgram;
    VAO* _vao;
    EBO* _ebo;
public:
    BrickpongBrick(b2World* aworld, b2Vec2 position, float awidth, float aheight, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc);
    virtual ~BrickpongBrick();
    b2Vec2 GetPosition();
    bool IsActive();
    void SetActive(bool aactive);
    void Draw(glm::mat4* Model, glm::mat4* View, glm::mat4* Projection, GLuint MVP_ID);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongBrick__) */
