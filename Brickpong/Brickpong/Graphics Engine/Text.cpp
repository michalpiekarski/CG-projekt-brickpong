#include "Text.h"

Text::Text(Window* awindow) : Text(awindow, "fonts/Arial.ttf") {
}

Text::Text(Window* awindow, unsigned short adebugMode) : Text(awindow, "fonts/Arial.ttf", adebugMode) {

}

Text::Text(Window* awindow, const char* afont) : Text(awindow, afont, 0) {

}

Text::Text(Window* awindow, const char* afont, unsigned short adebugMode) {
    _window = awindow;

    _debugMode = adebugMode;
    _shaderProgram = new ShaderProgram();
    Shader* vShader = new Shader("shaders/Text.vert", GL_VERTEX_SHADER);
    Shader* fShader = new Shader("shaders/Text.frag", GL_FRAGMENT_SHADER);
    _shaderProgram->attachShader(vShader);
    _shaderProgram->attachShader(fShader);
    _shaderProgram->link();
    _shaderProgram->use();
    delete vShader;
    delete fShader;

    if (_debugMode > 0) {
        std::cout << "Initializing FreeType..." << std::endl;
    }
    FT_Init_FreeType(&_ftLibrary);

    if(_debugMode > 0) {
        std::cout << "Initializing Font: " << afont << "..." << std::endl;
    }
    FT_New_Face(_ftLibrary, afont, 0, &_ftFace);
    FT_Set_Pixel_Sizes(_ftFace, 0, 64);

    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    GLint uniform_tex = _shaderProgram->getUniformLoc("tex");
    _uniform_color = _shaderProgram->getUniformLoc("color");
    glUniform1i(uniform_tex, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLint attribute_coord = _shaderProgram->getAttributeLoc("coord");
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);
    glBindVertexArray(NULL);
}

Text::~Text() {
    delete _shaderProgram;
}

void Text::DrawUnicode(const wchar_t* atext, float aposX, float aposY, float awidth, float aheight, int afontSize, GLfloat acolor[4]) {
    if(_debugMode > 1) {
        std::cout << "Rendering text: " << std::endl;
    }
    _shaderProgram->use();
    glBindVertexArray(_vao);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    int windowWidth, windowHeight;
    _window->getFrameBufferSize(&windowWidth, &windowHeight);
    float width = 2.0f / windowWidth;
    float height = 2.0f / windowHeight;
    aposX *= width;
    aposY *= height;
    awidth *= width;
    aheight *= height;

    FT_Set_Pixel_Sizes(_ftFace, 0, afontSize);
    glUniform4fv(_uniform_color, 1, acolor);

    const wchar_t *p;
    float startx = aposX;

    for(p = atext; *p; p++) {
        if(_debugMode > 1) {
            std::wcout << *p;
        }

        if(FT_Load_Char(_ftFace, *p, FT_LOAD_RENDER))
            continue;
        FT_GlyphSlot g = _ftFace->glyph;

        if(*p == L'\n') {
            aposX = startx;
            float tmpHeight = g->bitmap.rows != 0 ? g->bitmap.rows : 50;
            aposY -= tmpHeight * aheight * 1.25f;
            continue;
        }

        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     g->bitmap.width,
                     g->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     g->bitmap.buffer
                     );

        float x2 = aposX + g->bitmap_left * awidth;
        float y2 = -aposY - g->bitmap_top * aheight;
        float w = g->bitmap.width * awidth;
        float h = g->bitmap.rows * aheight;

        GLfloat box[4][4] = {
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 4 * 4, box, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        aposX += (g->advance.x >> 6) * awidth;
        aposY += (g->advance.y >> 6) * aheight;
    }
    if(_debugMode > 1) {
        std::wcout << std::endl;
    }

    glBindVertexArray(NULL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}
