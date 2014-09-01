#include "Window.h"
#include "../BrickpongException.h"

GLint Window::instanceCount = 0;

Window::Window(GLint width, GLint height, std::string title, bool fullscreen = false) {
    if (instanceCount == 0) {
        // Initialise GLFW
        if (!glfwInit()) {
            throw BrickpongException("Failed to initialize GLFW!");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    instanceCount++;

    GLFWmonitor* primaryMonitor = NULL;
    if (fullscreen) {
        primaryMonitor = glfwGetPrimaryMonitor();
    }
    // Open a window and create its OpenGL context
    _window = glfwCreateWindow(width, height, title.c_str(), primaryMonitor, NULL);
    if (!_window) {
        throw BrickpongException("Failed to open GLFW window!");
    }
}

Window::~Window() {
    glfwDestroyWindow(_window);
    instanceCount--;
    if (instanceCount == 0) {
        glfwTerminate();
    }
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(_window);

#ifdef __Brickpong__DEBUG_LOG__
    // Print supported OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#endif

    //Check if on Windows - both x86 and x64
#ifdef _WIN32
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        throw BrickpongException("Failed to initialize GLEW!");
    }
#endif
}

int Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

GLint Window::getFrameBufferWidth() {
    GLint width;
    glfwGetFramebufferSize(_window, &width, NULL);
    return width;
}

GLint Window::getFrameBufferHeight() {
    GLint height;
    glfwGetFramebufferSize(_window, NULL, &height);
    return height;
}
void Window::getFrameBufferSize(GLint* width, GLint* height) {
    glfwGetFramebufferSize(_window, width, height);
}

void Window::swapBuffers() {
    glfwSwapBuffers(_window);
}

void Window::setCursorMode(int mode) {
    glfwSetInputMode(_window, GLFW_CURSOR, mode);
}

void Window::setStickyKeys(int mode) {
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, mode);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(_window, callback);
}

void Window::setKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(_window, callback);
}

int Window::getKey(int key) {
    return glfwGetKey(_window, key);
}

int Window::getMouseButton(int mouseButton) {
    return glfwGetMouseButton(_window, mouseButton);
}

glm::dvec2 Window::getCursorPositionInWorldSpace(float aworldWidth, float aworldHeight, glm::vec2 aworldCenterOffset) {
    glm::dvec2 cursorPos;
    glfwGetCursorPos(_window, &cursorPos.x, &cursorPos.y);
    glm::ivec2 windowSize;
    glfwGetFramebufferSize(_window, &windowSize.x, &windowSize.y);
    float halfWindowWidth = windowSize.x / 2.0f;
    float halfWindowHeight = windowSize.y / 2.0f;
    cursorPos.x = (cursorPos.x - halfWindowWidth) / (halfWindowWidth / aworldWidth) + aworldCenterOffset.x;
    cursorPos.y = (cursorPos.y - halfWindowHeight) / (halfWindowHeight / aworldHeight) + aworldCenterOffset.y;
    return cursorPos;
}