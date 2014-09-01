#ifndef __Brickpong__GraphicsEngine__
#define __Brickpong__GraphicsEngine__

#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class GraphicsEngine {
private:
    bool _zoom = true;
public:
    GraphicsEngine();
    virtual ~GraphicsEngine();
    glm::mat4 ZoomOut(glm::vec3 atarget);
    glm::mat4 ZoomIn();
    glm::mat4 ChangeZoomLevel(Window* window, glm::mat4 currentMatrix);
    glm::mat4 ChangeToOrtographic();
    glm::mat4 ChangeToPerspective();
    glm::mat4 ChangeProjection();
    bool IsZoomed();
};

#endif /* defined(__Brickpong__GraphicsEngine__) */