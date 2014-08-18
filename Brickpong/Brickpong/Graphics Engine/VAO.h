#ifndef __Brickpong__VAO__
#define __Brickpong__VAO__

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

class VAO {
private:
    GLuint _VAOID;
public:
    VAO();
    virtual ~VAO();
    void bind();
    void unbind();
};

#endif /* defined(__Brickpong__VAO__) */