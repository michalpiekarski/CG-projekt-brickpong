#ifndef __Brickpong__EBO__
#define __Brickpong__EBO__

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

class EBO {
    GLuint _EBOID;

public:
    EBO();
    virtual ~EBO();
    
    void bind();
    void unbind();
    GLuint getID();
    void data(const GLvoid* data, GLsizeiptr dataSize, GLenum usage);
};

#endif /* defined(__Brickpong__EBO__) */
