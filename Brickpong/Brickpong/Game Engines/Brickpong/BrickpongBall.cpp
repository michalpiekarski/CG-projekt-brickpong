#include "BrickpongBall.h"


BrickpongBall::BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float adensity) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(1.0f, -5.0f);
    bodyDef.linearVelocity.Set(alinearVelocity.x, alinearVelocity.y);
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

void BrickpongBall::SetLinearVelocity(b2Vec2 alinearVelocity) {
    _body->SetLinearVelocity(alinearVelocity);
}
b2Vec2 BrickpongBall::GetPosition() {
    return _body->GetPosition();
}

void BrickpongBall::SetTransform(b2Vec2 aposition, float aangle) {
    _body->SetTransform(aposition, aangle);
}
