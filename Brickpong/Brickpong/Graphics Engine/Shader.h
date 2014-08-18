#ifndef __Brickpong__Shader__
#define __Brickpong__Shader__

#include <iostream>
#include <fstream>

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