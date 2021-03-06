#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &_VBOID);
}

VBO::VBO(GLfloat data[][3], int dataSize, GLenum usage) : VBO() {
    SetData(data, dataSize, usage);
}

VBO::VBO(aiVector3D* data, int dataSize, GLenum usage) : VBO() {
    SetData(data, dataSize, usage);
}

VBO::VBO(aiColor4D* data, int dataSize, GLenum usage) : VBO() {
    SetData(data, dataSize, usage);
}

VBO::~VBO() {
    unbind();
    glDeleteBuffers(1, &_VBOID);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _VBOID);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

GLuint VBO::getID() {
    return _VBOID;
}

void VBO::SetData(GLfloat data[][3], int dataSize, GLenum usage) {
    _dataSize = dataSize;
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * _dataSize, data, usage);
    unbind();
}

void VBO::SetData(aiVector3D* data, int dataSize, GLenum usage) {
    _dataSize = dataSize;
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * _dataSize, data, usage);
    unbind();
}

void VBO::SetData(aiColor4D* data, int dataSize, GLenum usage) {
    _dataSize = dataSize;
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * _dataSize, data, usage);
    unbind();
}

void VBO::createVertexAttribPointer(GLuint index, GLint size, GLenum type,
                                    GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
    glEnableVertexAttribArray(index);
    bind();
    glVertexAttribPointer(
        index,       // attribute. No particular reason for 0, but must match the layout in the shader.
        size,        // size
        type,        // type
        normalized,  // normalized?
        stride,      // stride
        pointer      // array buffer offset
        );
    unbind();
}