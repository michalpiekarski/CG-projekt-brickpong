#ifndef __Brickpong__VBO__
#define __Brickpong__VBO__

#ifdef _WIN32
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

class VBO {
private:
    GLuint _VBOID;
public:
    VBO();
    virtual ~VBO();

    void bind();
    void unbind();
    GLuint getID();
    void data(const GLvoid* data, GLsizeiptr dataSize, GLenum usage);
    void createVertexAttribPointer(GLuint index, GLint size, GLenum type,
                                   GLboolean normalized, GLsizei stride, const GLvoid* pointer);
};

#endif /* defined(__Brickpong__VBO__) */