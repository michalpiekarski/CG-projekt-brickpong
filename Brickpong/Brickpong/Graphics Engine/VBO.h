#ifndef __Brickpong__VBO__
#define __Brickpong__VBO__

#ifdef _WIN32
    #include <GL/glew.h>
    #ifndef GLFW_DLL
        #define GLFW_DLL
    #endif /* defined(GLFW_DLL) */
#endif /* included(GL/glew.h) */
#ifdef __APPLE__
    #ifndef GLFW_INCLUDE_GLCOREARB
        #define GLFW_INCLUDE_GLCOREARB
    #endif /* defined(GLFW_INCLUDE_GLCOREARB) */
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