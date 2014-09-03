#include "BrickpongBall.h"


BrickpongBall::BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float alinearVelocityMultiplier, float adensity, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc) {
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

    _shaderProgram = ashaderProgram;
    _shaderProgram->use();

    _vao = new VAO();
    _vao->bind();

    GLfloat vertex_data[9][3] = {
            {-1.0f, -1.0f, -1.0f, }, // 0-E
            {-1.0f, -1.0f, +1.0f, }, // 1-H
            {-1.0f, +1.0f, +1.0f, }, // 2-D
            {+1.0f, +1.0f, -1.0f, }, // 3-B
            {-1.0f, +1.0f, -1.0f, }, // 4-A
            {+1.0f, -1.0f, +1.0f, }, // 5-G
            {+1.0f, -1.0f, -1.0f, }, // 6-F
            {+1.0f, +1.0f, +1.0f, }, // 7-C
            {+0.0f, +0.0f, +1.0f, }, // 8-I
    };
    VBO* vVBO = new VBO(vertex_data, 9, GL_STATIC_DRAW);
    GLfloat color_data[9][3] = {
            {0.0f, 1.0f, 0.0f, }, // 0-E
            {1.0f, 0.0f, 0.0f, }, // 1-H
            {1.0f, 0.0f, 0.0f, }, // 2-D
            {0.0f, 0.0f, 1.0f, }, // 3-B
            {0.0f, 1.0f, 0.0f, }, // 4-A
            {1.0f, 0.0f, 0.0f, }, // 5-G
            {0.0f, 0.0f, 1.0f, }, // 6-F
            {1.0f, 0.0f, 0.0f, }, // 7-C
            {1.0f, 1.0f, 1.0f, }, // 8-I
    };
    VBO* cVBO = new VBO(color_data, 9, GL_STATIC_DRAW);
    GLushort index_data[14][3] = {
            {0, 1, 2, }, // EHD - left
            {0, 2, 4, }, // EDA - left
            {3, 0, 4, }, // BEA - back
            {3, 6, 0, }, // BFE - back
            {7, 6, 3, }, // CFB - right
            {6, 7, 5, }, // FCG - right
            {5, 0, 6, }, // GEF - bottom
            {5, 1, 0, }, // GHE - bottom
            {7, 3, 4, }, // CBA - top
            {7, 4, 2, }, // CAD - top
            //{7, 2, 5, }, // CDG - front
            //{2, 1, 5, }, // DHG - front
            {8, 2, 1, }, // IDH - front
            {8, 7, 2, }, // ICD - front
            {8, 5, 7, }, // IGC - front
            {8, 1, 5, }, // IHG - front
    };
    _ebo = new EBO(index_data, 14, GL_STATIC_DRAW);

    vVBO->createVertexAttribPointer(apositionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    cVBO->createVertexAttribPointer(acolorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

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

void BrickpongBall::Draw(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    _shaderProgram->use();

    glm::vec3 tmpBallPosition = glm::vec3(_body->GetPosition().x, _body->GetPosition().y, 0.0f);
    glm::mat4 tmpModel = glm::scale(glm::translate(Model, tmpBallPosition), glm::vec3(_radius, _radius, 0.25f));
    glm::mat4 MVP = Projection * View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    _vao->bind();
    _ebo->Draw();
    _vao->unbind();
}
