#ifndef __Brickpong__Window__
#define __Brickpong__Window__

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
};

#endif /* defined(__Brickpong__Window__) */