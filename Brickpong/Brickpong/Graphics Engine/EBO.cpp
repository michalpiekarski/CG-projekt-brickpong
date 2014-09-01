#include "EBO.h"

EBO::EBO() {
    glGenBuffers(1, &_EBOID);
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

void EBO::data(const GLvoid* data, GLsizeiptr dataSize, GLenum usage) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, usage);
    unbind();
}