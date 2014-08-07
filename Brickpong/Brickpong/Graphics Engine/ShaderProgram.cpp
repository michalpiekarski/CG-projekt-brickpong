#include "ShaderProgram.h"
#include "Shader.h"
#include "../BrickpongException.h"

ShaderProgram::ShaderProgram()
{
    _programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_programID);
}

void ShaderProgram::attachShader(Shader* shader)
{
    glAttachShader(_programID, shader->getID());
}

void ShaderProgram::bindFragDataLocation(GLint colorAttachement, std::string name)
{
    glBindFragDataLocation(_programID, colorAttachement, name.c_str());
}

void ShaderProgram::link()
{
    glLinkProgram(_programID);

    GLint linkStatus;

    glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        std::string msg("Shader program linking failed:\n");

        int errorLength;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar* linkError = new GLchar[errorLength + 1];
        glGetShaderInfoLog(_programID, errorLength, NULL, linkError);
        msg += linkError;
        throw BrickpongException(msg);
    }
}

void ShaderProgram::use()
{
    glUseProgram(_programID);
}

GLint ShaderProgram::getAttributeLoc(std::string name)
{
    return glGetAttribLocation(_programID, name.c_str());
}

GLint ShaderProgram::getUniformLoc(std::string name)
{
    return glGetUniformLocation(_programID, name.c_str());
}