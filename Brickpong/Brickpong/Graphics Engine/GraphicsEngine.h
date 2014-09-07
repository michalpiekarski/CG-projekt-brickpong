#ifndef __Brickpong__GraphicsEngine__
#define __Brickpong__GraphicsEngine__

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
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Text.h"

class GraphicsEngine {
private:
    bool _zoom = true;
public:
    GraphicsEngine();
    virtual ~GraphicsEngine();
    glm::mat4 ZoomOut(glm::vec3 atarget);
    glm::mat4 ZoomIn();
    glm::mat4 ChangeZoomLevel(Window* window, glm::mat4* currentMatrix);
    glm::mat4 ChangeToPerspective();
    bool IsZoomed();
    bool Load3DFile(const char* afilePath, ShaderProgram* ashaderProgram, EBO* aebo, VBO* avvbo, VBO* acvbo);
};

#endif /* defined(__Brickpong__GraphicsEngine__) */