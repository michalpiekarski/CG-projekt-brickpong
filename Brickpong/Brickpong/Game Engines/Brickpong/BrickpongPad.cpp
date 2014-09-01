#include "BrickpongPad.h"

BrickpongPad::BrickpongPad(b2World* aworld,float awidth, float aheight, float acursorPositionX) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(acursorPositionX, -7.5f);
    _body = aworld->CreateBody(&bodyDef);
    b2Vec2 shapePoints[6] = {
        b2Vec2(-awidth/2.0f, -aheight/2.0f),
        b2Vec2(-awidth/2.0f, -aheight/4.0f),
        b2Vec2(-awidth/4.0f, +aheight/2.0f),
        b2Vec2(+awidth/4.0f, +aheight/2.0f),
        b2Vec2(+awidth/2.0f, -aheight/4.0f),
        b2Vec2(+awidth/2.0f, -aheight/2.0f),
    };
    b2PolygonShape shape;
    shape.Set(shapePoints, 6);
    _body->CreateFixture(&shape, 0.0f);
}


BrickpongPad::~BrickpongPad() {
}

b2Vec2 BrickpongPad::GetPosition() {
    return _body->GetPosition();
}

float BrickpongPad::GetAngle() {
    return _body->GetAngle();
}

void BrickpongPad::SetTransform(b2Vec2 aposition, float aangle) {
    _body->SetTransform(aposition, aangle);
}
