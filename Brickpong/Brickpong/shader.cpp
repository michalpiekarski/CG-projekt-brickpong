#include "Shader.h"
#include "BrickpongException.h"

Shader::Shader(std::string path, GLenum type)
{
    _shaderID = CreateShaderFromFile(path.c_str(), type);
}

Shader::~Shader()
{
    glDeleteShader(_shaderID);
}

GLuint Shader::CreateShaderFromFile(const GLchar* path, GLenum type)
{
    // Create the shaders
    GLuint shaderID = glCreateShader(type);

    // Read the Vertex Shader code from the file
    std::ifstream shaderStream(path);
    if (!shaderStream.is_open())
    {
        std::string msg = "Impossible to open shader file: ";
        msg += path;
        throw BrickpongException(msg);
    }

    std::string source((std::istreambuf_iterator<GLchar>(shaderStream)), std::istreambuf_iterator<GLchar>());
    shaderStream.close();

    // Compile Vertex Shader
    std::cout << "Compiling shader : " << path << std::endl;
    char const * shaderSource = source.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);

    GLint compileStatus = GL_FALSE;

    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        std::string msg("Shader '");
        msg += path;
        msg += "' failed to compile!\n";

        int errorLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);
        GLchar* compileError = new GLchar[errorLength + 1];
        glGetShaderInfoLog(shaderID, errorLength, NULL, compileError);
        msg += compileError;
        throw BrickpongException(msg);
    }

    return shaderID;
}

GLuint Shader::getID()
{
    return _shaderID;
}
