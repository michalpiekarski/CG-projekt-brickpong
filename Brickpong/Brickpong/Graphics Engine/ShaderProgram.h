#ifndef __Brickpong__ShaderProgram__
#define __Brickpong__ShaderProgram__

#include <iostream>

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

class Shader;

class ShaderProgram {
private:
    GLuint _programID;

public:
    ShaderProgram();
    virtual ~ShaderProgram();
    void attachShader(Shader* shader);
    void bindFragDataLocation(GLint colorAttachement, std::string name);
    void link();
    void use();
    GLint getAttributeLoc(std::string name);
    GLint getUniformLoc(std::string name);
};

#endif /* defined(__Brickpong__ShaderProgram__) */