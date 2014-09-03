#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine() {

}

GraphicsEngine::~GraphicsEngine() {

}

glm::mat4 GraphicsEngine::ZoomOut(glm::vec3 atarget) {
    _zoom = false;
    return glm::lookAt(glm::vec3(0.0f, 0.0f, 30.0f), atarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 GraphicsEngine::ZoomIn() {
    _zoom = true;
    return glm::lookAt(glm::vec3(0.0f, -3.0f, 10.0f), glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 GraphicsEngine::ChangeZoomLevel(Window* window, glm::mat4 currentMatrix) {
    if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        return ZoomIn();
    }
    else if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glm::dvec2 target = window->getCursorPositionInWorldSpace(45.0f, 10.0f, glm::vec2(0.0f, -8.0f));
        return ZoomOut(glm::vec3(target.x, target.y, 0.0f));
    }
    else {
        return currentMatrix;
    }
}

glm::mat4 GraphicsEngine::ChangeToPerspective() {
    return glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
}

bool GraphicsEngine::IsZoomed() {
    return _zoom;
}