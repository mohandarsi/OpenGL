#include "orthographicProjection.h"

#include <GLFW/glfw3.h> // for GLFW_KEY_SPACE
#include <glm/glm.hpp>

OrthographicProjection::OrthographicProjection():
  DemoBase("resources/baseColor.vs", "resources/baseColor.fs"),
  m_viewportSize(800,600),
  m_mvp(glm::mat4(1.))
{

}

void OrthographicProjection::init()
{
  m_mesh.SetVertices( {
        glm::vec3(10.0f, 150.0f, -1.0f), // left  
        glm::vec3(400.f, 150.0f, -1.0f), // right 
        glm::vec3(200.0f, 20.0f, -1.0f)  // top   
    } );

   m_mesh.SetColors({ glm::vec4(1.,0.,0.,1) ,glm::vec4(0.,1.,0.,1),glm::vec4(0.,0.,1.,1)}); //RGB
      
  std::cout<< "No traingle is visible because coordinates are not in the NDC space  and we did not apply any projection matrix(or transformations). \
  "<< std::endl;

  std::cout<< "Press any key to toggle (and to apply projection matrix)." << std::endl;

}

void OrthographicProjection::onViewportSizeChanged(const int& width, const int& height)
{
    m_viewportSize = glm::vec2(width, height);
}

void OrthographicProjection::onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods)
{

  if(action != GLFW_RELEASE) return;

  const auto isIdentity =  (glm::mat4(1.) == m_mvp);
  
  if(isIdentity)
  {
    const auto focusPosition = m_viewportSize/2.f;  //always middle of the screen.
    // Set orthographic projection Configured top-left corner as (0, 0)
    glm::mat4 orthographicMatrix = glm::mat4(1.0f);
    m_mvp = getProjectionMatrix(m_viewportSize,focusPosition,1);
  }
  else
  {
    m_mvp =  glm::mat4(1.);
  }
}

void OrthographicProjection::draw()
{
    m_shader.use();  
    m_shader.setMat4("mvp",m_mvp);
    m_mesh.Draw();
}