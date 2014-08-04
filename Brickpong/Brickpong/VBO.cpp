#include "VBO.h"

VBO::VBO()
{
    glGenBuffers(1, &_VBOID);
}

VBO::~VBO()
{
    unbind();
    glDeleteBuffers(1, &_VBOID);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _VBOID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

GLuint VBO::getID()
{
    return _VBOID;
}

void VBO::data(const GLvoid* data, GLsizeiptr dataSize, GLenum usage)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, usage);
    unbind();
}