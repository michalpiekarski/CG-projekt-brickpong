#ifndef __Brickpong__Graphics_Engine__Text__
#define __Brickpong__Graphics_Engine__Text__

#ifdef _WIN32
#define GLEW_STATIC
#include <GL\glew.h>
#endif
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "GraphicsEngine.h"

class Text {
private:
    Window* _window;
    ShaderProgram* _shaderProgram;
    GLuint _vao;
    GLint _uniform_color;
    FT_Library _ftLibrary;
    FT_Face _ftFace;
    FT_GlyphSlot _ftGlyphSlot;
    unsigned short _debugMode;
public:
    Text(Window* awindow);
    Text(Window* awindow, unsigned short adebugMode);
    Text(Window* awindow, const char* afont);
    Text(Window* awindow, const char* afont, unsigned short adebugMode);
    virtual ~Text();
    void DrawUnicode(const wchar_t* atext, float aposX, float aposY, int afontSize, GLfloat acolor[4]);
};

#endif /* defined(__Brickpong__Graphics_Engine__Text__) */
