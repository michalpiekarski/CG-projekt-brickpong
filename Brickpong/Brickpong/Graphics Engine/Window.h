#ifndef __Brickpong__Window__
#define __Brickpong__Window__

#include <iostream>

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {
private:
    static GLint instanceCount;

    GLFWwindow* _window;
public:
    Window(GLint width, GLint height, std::string title, bool fullscreen);
    virtual ~Window();

    void makeContextCurrent();
    int shouldClose();
    GLint getFrameBufferWidth();
    GLint getFrameBufferHeight();
    void getFrameBufferSize(GLint* width, GLint* height);
    void swapBuffers();
    void setCursorMode(int mode);
    void setStickyKeys(int mode);
    void setCursorPosCallback(GLFWcursorposfun callback);
    void setKeyCallback(GLFWkeyfun callback);
    int getKey(int key);
    int getMouseButton(int mouseButton);
    glm::dvec2 getCursorPositionInWorldSpace(float aworldWidth, float aworldHeight, glm::vec2 aworldCenterOffset);
};

#endif /* defined(__Brickpong__Window__) */