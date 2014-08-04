#ifndef __Brickpong__ShaderProgram__
#define __Brickpong__ShaderProgram__

#include <iostream>

#ifdef _WIN32
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
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