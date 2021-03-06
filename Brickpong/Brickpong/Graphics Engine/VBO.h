#ifndef __Brickpong__VBO__
#define __Brickpong__VBO__

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <assimp/mesh.h>

class VBO {
private:
    GLuint _VBOID;
    int _dataSize;

public:
    VBO();
    VBO(GLfloat data[][3], int dataSize, GLenum usage);
    VBO(aiVector3D* data, int dataSize, GLenum usage);
    VBO(aiColor4D* data, int dataSize, GLenum usage);
    virtual ~VBO();

    void bind();
    void unbind();
    GLuint getID();
    void SetData(GLfloat data[][3], int dataSize, GLenum usage);
    void SetData(aiVector3D* data, int dataSize, GLenum usage);
    void SetData(aiColor4D* data, int dataSize, GLenum usage);
    void createVertexAttribPointer(GLuint index, GLint size, GLenum type,
                                   GLboolean normalized, GLsizei stride, const GLvoid* pointer);
};

#endif /* defined(__Brickpong__VBO__) */