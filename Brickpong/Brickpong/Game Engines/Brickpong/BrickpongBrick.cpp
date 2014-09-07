#include "BrickpongBrick.h"


BrickpongBrick::BrickpongBrick(b2World* aworld, b2Vec2 aposition, float awidth, float aheight, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc) {
    _width = awidth;
    _height = aheight;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(aposition.x, aposition.y);
    _body = aworld->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(awidth / 2.0f, aheight / 2.0f);
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
            {0.0f, 0.0f, 1.0f, }, // 0-E
            {0.0f, 1.0f, 0.0f, }, // 1-H
            {0.0f, 1.0f, 0.0f, }, // 2-D
            {1.0f, 0.0f, 0.0f, }, // 3-B
            {0.0f, 0.0f, 1.0f, }, // 4-A
            {0.0f, 1.0f, 0.0f, }, // 5-G
            {1.0f, 0.0f, 0.0f, }, // 6-F
            {0.0f, 1.0f, 0.0f, }, // 7-C
            {0.0f, 0.0f, 0.0f, }, // 8-I
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

void BrickpongBrick::Draw(glm::mat4* Model, glm::mat4* View, glm::mat4* Projection, GLuint MVP_ID) {
    _shaderProgram->use();

    b2Vec2 bodyPos = _body->GetPosition();
    glm::vec3 translation = glm::vec3(bodyPos.x, bodyPos.y, 0.0f);
    glm::vec3 scale = glm::vec3(_width/2.0f, _height/2.0f, 0.25f);
    glm::mat4 tmpModel = glm::scale(glm::translate(*Model, translation), scale);
    glm::mat4 MVP = *Projection * *View * tmpModel;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);

    _vao->bind();
    _ebo->Draw();
    _vao->unbind();
}