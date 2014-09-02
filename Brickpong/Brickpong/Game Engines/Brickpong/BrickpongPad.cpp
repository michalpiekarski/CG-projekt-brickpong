#include "BrickpongPad.h"
#include "BrickpongGame.h"

BrickpongPad::BrickpongPad(b2World* aworld,float awidth, float aheight, float acursorPositionX) {
    _width = awidth;
    _height = aheight;
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

void BrickpongPad::Draw(Cursor* aCursor, EBO* aEBO, glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    glm::mat4 tmpModel = glm::scale(glm::translate(Model, glm::vec3(aCursor->positionX, -7.5f, 0)), glm::vec3(_width/2.0f, _height/2.0f, 1.0f));
    glm::mat4 MVP = Projection * View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    aEBO->Draw();
}
