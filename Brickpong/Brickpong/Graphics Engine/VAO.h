#ifndef __Brickpong__VAO__
#define __Brickpong__VAO__

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
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