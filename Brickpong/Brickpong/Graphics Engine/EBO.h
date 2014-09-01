#ifndef __Brickpong__EBO__
#define __Brickpong__EBO__

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

class EBO {
    GLuint _EBOID;
    int _dataSize;

public:
    EBO();
    EBO(GLushort data[][3], int dataSize, GLenum usage);
    virtual ~EBO();

    void bind();
    void unbind();
    GLuint getID();
    void SetData(GLushort data[][3], int dataSize, GLenum usage);
    void Draw();
};

#endif /* defined(__Brickpong__EBO__) */
