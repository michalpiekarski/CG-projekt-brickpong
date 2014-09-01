#include "BrickpongBrick.h"


BrickpongBrick::BrickpongBrick(b2World* aworld, b2Vec2 aposition, float awidth, float aheight) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(aposition.x, aposition.y);
    _body = aworld->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(awidth / 2.0f, aheight / 2.0f);
    _body->CreateFixture(&shape, 0.0f);
}


BrickpongBrick::~BrickpongBrick() {
}

b2Vec2 BrickpongBrick::GetPosition() {
    return _body->GetPosition();
}

bool BrickpongBrick::IsActive() {
    return _body->IsActive();
}

void BrickpongBrick::SetActive(bool aactive) {
    _body->SetActive(aactive);
}