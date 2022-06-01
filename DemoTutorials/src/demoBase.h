#pragma once

#include "shader.h"
#include "mesh.h"
#include <iostream>

class DemoBase
{
public:
    DemoBase(const char* vertexPath, const char* fragmentPath);
    virtual ~DemoBase() {};
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual std::string getInstructions() const = 0;

    virtual void onViewportSizeChanged(const int& width, const int& height){};
    virtual void onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods){};

protected:
    glm::mat4 getProjectionMatrix(const glm::vec2& viewportSize,const glm::vec2& focusPosition, const GLfloat& zoom);

protected:
    Shader m_shader;
    Mesh m_mesh;
};