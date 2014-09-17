#include "BrickpongBall.h"


BrickpongBall::BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float alinearVelocityMultiplier, float adensity, GraphicsEngine* agraphicsEngine, ShaderProgram* ashaderProgram) {
    _radius = aradius;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.0f, -5.0f);
    _linearVelocityMultiplier = alinearVelocityMultiplier;
    bodyDef.linearVelocity.Set(alinearVelocity.x*_linearVelocityMultiplier, alinearVelocity.y*_linearVelocityMultiplier);
    bodyDef.gravityScale = 0.0f;
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.0f;
    bodyDef.bullet = true;
    _body = aworld->CreateBody(&bodyDef);
    b2CircleShape shape;
    shape.m_radius = aradius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = adensity;
    fixtureDef.friction = 0.01f;
    fixtureDef.restitution = 1.0f;
    _body->CreateFixture(&fixtureDef);

    _graphicsEngine = agraphicsEngine;

    _shaderProgram = ashaderProgram;
    _shaderProgram->use();

    _vao = new VAO();
    _vao->bind();

    VBO* vvbo = new VBO();
    VBO* cvbo = new VBO();
    VBO* nvbo = new VBO();
    _ebo = new EBO();

    if (!_graphicsEngine->Load3DFile("meshes/ball.fbx", _shaderProgram, _ebo, vvbo, cvbo, nvbo)) {
        exit(EXIT_FAILURE);
    }

    _vao->unbind();
}


BrickpongBall::~BrickpongBall() {
}

b2Body* BrickpongBall::GetBody() {
    return _body;
}

b2Vec2 BrickpongBall::GetLinearVelocity() {
    return _body->GetLinearVelocity();
}

float BrickpongBall::GetLinearVelocityMultiplier() {
    return _linearVelocityMultiplier;
}
void BrickpongBall::SetLinearVelocityMultiplier(float alinearVelocityMultiplier) {
    float tmpVelMulti = _linearVelocityMultiplier;
    _linearVelocityMultiplier = glm::clamp(alinearVelocityMultiplier, 0.25f, 4.0f);
    if (_linearVelocityMultiplier != tmpVelMulti) {
        SetLinearVelocity(GetLinearVelocity());
    }
}

void BrickpongBall::SetLinearVelocity(b2Vec2 alinearVelocity) {
    b2Vec2 tmpLinearVel = b2Vec2(alinearVelocity.x*_linearVelocityMultiplier, alinearVelocity.y*_linearVelocityMultiplier);
    _body->SetLinearVelocity(tmpLinearVel);
}
b2Vec2 BrickpongBall::GetPosition() {
    return _body->GetPosition();
}

void BrickpongBall::SetTransform(b2Vec2 aposition, float aangle) {
    _body->SetTransform(aposition, aangle);
}

void BrickpongBall::Draw(glm::mat4* Model, glm::mat4* View, glm::mat4* Projection) {
    _shaderProgram->use();

    GLuint ballViewUniformLoc = _shaderProgram->getUniformLoc("View");
    glUniformMatrix4fv(ballViewUniformLoc, 1, GL_FALSE, &(*View)[0][0]);
    GLuint ballProjectionUniformLoc = _shaderProgram->getUniformLoc("Projection");
    glUniformMatrix4fv(ballProjectionUniformLoc, 1, GL_FALSE, &(*Projection)[0][0]);

    glm::vec3 tmpBallPosition = glm::vec3(_body->GetPosition().x, _body->GetPosition().y, 0.0f);
    
    glm::mat4 tmpModel = glm::translate(*Model, tmpBallPosition);
    tmpModel = glm::rotate(tmpModel, -_body->GetAngle()*2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    tmpModel = glm::scale(tmpModel, glm::vec3(0.05f, 0.05f, 0.05f));

    GLuint ballModelUniformLoc = _shaderProgram->getUniformLoc("Model");
    glUniformMatrix4fv(ballModelUniformLoc, 1, GL_FALSE, &tmpModel[0][0]);

    GLuint lightPositionUniformLoc = _shaderProgram->getUniformLoc("LightPosition");
    glm::vec3 LightPosition = glm::vec3(0.0f, -3.0f, 1.0f);
    glUniform3fv(lightPositionUniformLoc, 1, &LightPosition[0]);

    _vao->bind();
    _ebo->Draw();
    _vao->unbind();
}
