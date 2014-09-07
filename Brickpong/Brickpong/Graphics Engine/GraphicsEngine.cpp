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

glm::mat4 GraphicsEngine::ChangeZoomLevel(Window* window, glm::mat4* currentMatrix) {
    if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        return ZoomIn();
    }
    else if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glm::dvec2 target = window->getCursorPositionInWorldSpace(45.0f, 10.0f, glm::vec2(0.0f, -8.0f));
        return ZoomOut(glm::vec3(target.x, target.y, 0.0f));
    }
    else {
        return *currentMatrix;
    }
}

glm::mat4 GraphicsEngine::ChangeToPerspective() {
    return glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);
}

bool GraphicsEngine::IsZoomed() {
    return _zoom;
}


bool GraphicsEngine::Load3DFile(const char* afilePath, ShaderProgram* ashaderProgram, EBO* aebo, VBO* avvbo, VBO* acvbo) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(afilePath,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);
    if (!scene) {
        std::cerr << "Wczytywanie: " << afilePath << " nie powiod³o siê!" << std::endl;
        return false;
    }

    if (scene->HasMeshes()) {
        aiMesh* mesh = scene->mMeshes[0];
        int numVertices = mesh->mNumVertices;
        if (mesh->HasPositions()) {
            GLint positionAttribLoc = ashaderProgram->getAttributeLoc("position");
            avvbo->SetData(mesh->mVertices, numVertices, GL_STATIC_DRAW);
            avvbo->createVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        }
        // TODO: Sprawdziæ dlaczego w plikach obj i fbx nie ma vertex color
        GLint colorAttribLoc = ashaderProgram->getAttributeLoc("color");
        GLfloat color_data[24][3] = {
                {0.0f, 0.0f, 1.0f, }, // 0-E
                {0.0f, 1.0f, 0.0f, }, // 1-H
                {0.0f, 1.0f, 0.0f, }, // 2-D
                {1.0f, 0.0f, 0.0f, }, // 3-B
                {0.0f, 0.0f, 1.0f, }, // 4-A
                {0.0f, 1.0f, 0.0f, }, // 5-G
                {1.0f, 0.0f, 0.0f, }, // 6-F
                {0.0f, 1.0f, 0.0f, }, // 7-C
                {0.0f, 0.0f, 1.0f, }, // 0-E
                {0.0f, 1.0f, 0.0f, }, // 1-H
                {0.0f, 1.0f, 0.0f, }, // 2-D
                {1.0f, 0.0f, 0.0f, }, // 3-B
                {0.0f, 0.0f, 1.0f, }, // 4-A
                {0.0f, 1.0f, 0.0f, }, // 5-G
                {1.0f, 0.0f, 0.0f, }, // 6-F
                {0.0f, 1.0f, 0.0f, }, // 7-C
                {0.0f, 1.0f, 0.0f, }, // 2-D
                {1.0f, 0.0f, 0.0f, }, // 3-B
                {0.0f, 0.0f, 1.0f, }, // 4-A
                {0.0f, 1.0f, 0.0f, }, // 5-G
                {1.0f, 0.0f, 0.0f, }, // 6-F
                {0.0f, 1.0f, 0.0f, }, // 7-C
        };
        acvbo->SetData(color_data, numVertices, GL_STATIC_DRAW);
        acvbo->createVertexAttribPointer(colorAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        // ------------------------------------------------------------------
        if (mesh->HasFaces()) {
            std::vector<glm::uvec3> index_data;

            for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
                const aiFace* face = &mesh->mFaces[t];
                glm::uvec3 index = glm::uvec3();
                index.x = face->mIndices[0];
                index.y = face->mIndices[1];
                index.z = face->mIndices[2];
                index_data.push_back(index);
            }

            aebo->SetData(index_data, mesh->mNumFaces, GL_STATIC_DRAW);
        }
    }

    return true;
}
