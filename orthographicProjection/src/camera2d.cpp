#include "camera2d.h"
#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D(const glm::vec2& viewportSize,const glm::vec2& focusPosition, const GLfloat& zoom):
  m_viewportSize(viewportSize),
  m_focusPosition(focusPosition),
  m_zoom(zoom)
{
}

glm::mat4 Camera2D::getProjectionMatrix()
{
    // Set orthographic projection Configured top-left corner as (0, 0)
    double left = m_focusPosition.x - m_viewportSize.x/2.0;
    double right = m_focusPosition.x + m_viewportSize.x/2.0;
    double top = m_focusPosition.y - m_viewportSize.y/2.0;
    double bottom = m_focusPosition.y + m_viewportSize.y/2.0;

    glm::mat4 orthographicMatrix = glm::mat4(1.0f);
    orthographicMatrix = glm::ortho(left, right, bottom, top, 0.1, 100.0);
    
      
    return glm::scale(orthographicMatrix,glm::vec3(m_zoom));;
}