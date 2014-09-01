#include "BrickpongWorldBounds.h"


BrickpongWorldBounds::BrickpongWorldBounds(b2World* aworld, float awidth, float aheight, b2Vec2 acenterOffset) {
    b2BodyDef wbBDef;
    wbBDef.type = b2_kinematicBody;
    wbBDef.position.SetZero();
    _body = aworld->CreateBody(&wbBDef);

    float32 leftWindowEdge = -awidth / 2.0 + acenterOffset.x;
    float32 rightWindowEdge = awidth / 2.0 + acenterOffset.x;
    float32 topWindowEdge = aheight / 2.0 + acenterOffset.y;
    float32 bottomWindowEdge = -aheight / 2.0 + acenterOffset.y;

    b2Vec2 shapePoints[4] = {
        b2Vec2(leftWindowEdge, bottomWindowEdge),
        b2Vec2(leftWindowEdge, topWindowEdge),
        b2Vec2(rightWindowEdge, topWindowEdge),
        b2Vec2(rightWindowEdge, bottomWindowEdge),
    };

    b2ChainShape shape;
    shape.CreateChain(shapePoints, 4);
    _body->CreateFixture(&shape, 0.0f);
}


BrickpongWorldBounds::~BrickpongWorldBounds() {
}
