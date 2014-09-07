#ifndef __Brickpong__EBO__
#define __Brickpong__EBO__

#include <vector>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class EBO {
    GLuint _EBOID;
    int _dataSize;

public:
    EBO();
    EBO(GLuint data[][3], int dataSize, GLenum usage);
    EBO(std::vector<glm::uvec3> data, int dataSize, GLenum usage);
    virtual ~EBO();

    void bind();
    void unbind();
    GLuint getID();
    void SetData(GLuint data[][3], int dataSize, GLenum usage);
    void SetData(std::vector<glm::uvec3> data, int dataSize, GLenum usage);
    void Draw();
};

#endif /* defined(__Brickpong__EBO__) */
