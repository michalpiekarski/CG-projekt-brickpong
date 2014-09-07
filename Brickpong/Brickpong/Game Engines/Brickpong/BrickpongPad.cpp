#include "BrickpongPad.h"
#include "BrickpongGame.h"

BrickpongPad::BrickpongPad(b2World* aworld, float awidth, float aheight, float acursorPositionX, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc) {
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
            {0.0f, 0.0f, 1.0f, }, // 1-H
            {0.0f, 0.0f, 1.0f, }, // 2-D
            {1.0f, 0.0f, 0.0f, }, // 3-B
            {0.0f, 1.0f, 0.0f, }, // 4-A
            {0.0f, 0.0f, 1.0f, }, // 5-G
            {1.0f, 0.0f, 0.0f, }, // 6-F
            {0.0f, 0.0f, 1.0f, }, // 7-C
            {1.0f, 1.0f, 1.0f, }, // 8-I
    };
    VBO* cVBO = new VBO(color_data, 9, GL_STATIC_DRAW);
    GLuint index_data[14][3] = {
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

void BrickpongPad::Draw(Cursor* aCursor, glm::mat4* Model, glm::mat4* View, glm::mat4* Projection, GLuint MVP_ID) {
    _shaderProgram->use();

    glm::mat4 tmpModel = glm::scale(glm::translate(*Model, glm::vec3(aCursor->positionX, -7.5f, 0)), glm::vec3(_width/2.0f, _height/2.0f, 1.0f));
    glm::mat4 MVP = *Projection * *View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    _vao->bind();
    _ebo->Draw();
    _vao->unbind();
}
