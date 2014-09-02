#include "BrickpongBrick.h"


BrickpongBrick::BrickpongBrick(b2World* aworld, b2Vec2 aposition, float awidth, float aheight) {
    _width = awidth;
    _height = aheight;
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

void BrickpongBrick::Draw(EBO* aEBO, glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    b2Vec2 bodyPos = _body->GetPosition();
    glm::vec3 translation = glm::vec3(bodyPos.x, bodyPos.y, 0.0f);
    glm::vec3 scale = glm::vec3(_width/2.0f, _height/2.0f, 0.25f);
    glm::mat4 tmpModel = glm::scale(glm::translate(Model, translation), scale);
    glm::mat4 MVP = Projection * View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);
    aEBO->Draw();
}