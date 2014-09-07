#include "EBO.h"

EBO::EBO() {
    glGenBuffers(1, &_EBOID);
}

EBO::EBO(GLuint data[][3], int dataSize, GLenum usage) : EBO() {
    SetData(data, dataSize, usage);
}

EBO::EBO(std::vector<glm::uvec3> data, int dataSize, GLenum usage) : EBO() {
    SetData(data, dataSize, usage);
}

EBO::~EBO() {
    unbind();
    glDeleteBuffers(1, &_EBOID);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBOID);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

GLuint EBO::getID() {
    return _EBOID;
}

void EBO::SetData(GLuint data[][3], int dataSize, GLenum usage) {
    _dataSize = dataSize;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * _dataSize, data, usage);
    unbind();
}

void EBO::SetData(std::vector<glm::uvec3> data, int dataSize, GLenum usage) {
    _dataSize = dataSize;
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::uvec3) * _dataSize, &data[0], usage);
    unbind();
}

void EBO::Draw() {
    bind();
    glDrawElements(GL_TRIANGLES, _dataSize * 3, GL_UNSIGNED_INT, NULL);
    unbind();
}