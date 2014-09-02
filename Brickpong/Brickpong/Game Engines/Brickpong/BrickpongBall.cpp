#include "BrickpongBall.h"


BrickpongBall::BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float alinearVelocityMultiplier, float adensity) {
    _radius = aradius;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.0f, -5.0f);
    _linearVelocityMultiplier = alinearVelocityMultiplier;
    bodyDef.linearVelocity.Set(alinearVelocity.x*_linearVelocityMultiplier, alinearVelocity.y*_linearVelocityMultiplier);
    bodyDef.gravityScale = 0.0f;
    bodyDef.linearDamping = 0.0f;
    bodyDef.bullet = true;
    _body = aworld->CreateBody(&bodyDef);
    b2CircleShape shape;
    shape.m_radius = aradius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = adensity;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    _body->CreateFixture(&fixtureDef);
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

void BrickpongBall::Draw(EBO* aEBO, glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    glm::vec3 tmpBallPosition = glm::vec3(_body->GetPosition().x, _body->GetPosition().y, 0.0f);
    glm::mat4 tmpModel = glm::scale(glm::translate(Model, tmpBallPosition), glm::vec3(_radius, _radius, 0.25f));
    glm::mat4 MVP = Projection * View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    aEBO->Draw();
}
