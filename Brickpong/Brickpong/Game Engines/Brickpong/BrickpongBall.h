#ifndef __Brickpong__Game_engines__Brickpong__BrickpongBall__
#define __Brickpong__Game_engines__Brickpong__BrickpongBall__

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../../Graphics Engine/GraphicsEngine.h"

class BrickpongBall {
private:
    b2Body* _body;
    float _radius;
    float _density;
    float _linearVelocityMultiplier;
    GraphicsEngine* _graphicsEngine;
    ShaderProgram* _shaderProgram;
    VAO* _vao;
    EBO* _ebo;
public:
    BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float alinearVelocityMultiplier, float adensity, GraphicsEngine* agraphicsEngine, ShaderProgram* ashaderProgram);
    virtual ~BrickpongBall();
    b2Body* GetBody();
    b2Vec2 GetLinearVelocity();
    float GetLinearVelocityMultiplier();
    void SetLinearVelocityMultiplier(float alinearVelocityMultiplier);
    void SetLinearVelocity(b2Vec2 alinearVelocity);
    b2Vec2 GetPosition();
    void SetTransform(b2Vec2 aposition, float aangle);
    void Draw(glm::mat4* Model, glm::mat4* View, glm::mat4* Projection);
};

#endif /* defined(__Brickpong__Game_engines__Brickpong__BrickpongBall__) */
