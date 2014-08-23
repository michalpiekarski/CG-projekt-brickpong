#ifndef __Brickpong__Shader__
#define __Brickpong__Shader__

#include <iostream>
#include <fstream>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

class Shader {
private:
    GLuint _shaderID;

    GLuint CreateShaderFromFile(const GLchar* path, GLenum type);
public:
    Shader(std::string path, GLenum type);
    virtual ~Shader();

    GLuint getID();
};

#endif /* defined(__Brickpong__Shader__)*/