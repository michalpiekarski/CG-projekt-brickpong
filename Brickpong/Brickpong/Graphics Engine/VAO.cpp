#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &_VAOID);
}

VAO::~VAO()
{
    unbind();
    glDeleteVertexArrays(1, &_VAOID);
}

void VAO::bind()
{
    glBindVertexArray(_VAOID);
}

void VAO::unbind()
{
    glBindVertexArray(NULL);
}