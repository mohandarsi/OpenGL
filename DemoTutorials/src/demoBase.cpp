#include "demoBase.h"
#include <glm/gtc/matrix_transform.hpp>

DemoBase::DemoBase(const char* vertexPath, const char* fragmentPath):
  m_shader(vertexPath, fragmentPath)
{

}

glm::mat4 DemoBase::getProjectionMatrix(const glm::vec2& viewportSize,const glm::vec2& focusPosition, const GLfloat& zoom)
{
    // Set orthographic projection Configured top-left corner as (0, 0)
    double left = focusPosition.x - viewportSize.x/2.0;
    double right = focusPosition.x + viewportSize.x/2.0;
    double top = focusPosition.y - viewportSize.y/2.0;
    double bottom = focusPosition.y + viewportSize.y/2.0;

    glm::mat4 orthographicMatrix = glm::mat4(1.0f);
    orthographicMatrix = glm::ortho(left, right, bottom, top, 0.1, 100.0);
    
    
    return glm::scale(orthographicMatrix,glm::vec3(zoom));;
}