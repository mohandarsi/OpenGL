#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera2D
{

public:
    Camera2D(const glm::vec2& viewportSize, const glm::vec2& focusPosition, const GLfloat& zoom);
    glm::mat4 getProjectionMatrix();

private:
    glm::vec2 m_viewportSize;
    glm::vec2 m_focusPosition;
    GLfloat m_zoom;
};