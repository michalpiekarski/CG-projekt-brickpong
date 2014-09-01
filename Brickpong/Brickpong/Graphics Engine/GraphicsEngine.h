#ifndef __Brickpong__GraphicsEngine__
#define __Brickpong__GraphicsEngine__

#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class GraphicsEngine {
public:
    GraphicsEngine();
    virtual ~GraphicsEngine();
};

#endif /* defined(__Brickpong__GraphicsEngine__) */