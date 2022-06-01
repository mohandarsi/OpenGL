#include "modelTransformation.h"

#include <GLFW/glfw3.h> // for GLFW_KEY_SPACE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>      // std::stringstream

ModelTransformation::ModelTransformation():
  DemoBase("resources/baseColor.vs", "resources/baseColor.fs"),
  m_viewportSize(800,600)
{

}

void ModelTransformation::init()
{
   m_mesh.SetVertices({
          // first triangle
         glm::vec3(0.25f,  0.25f, -1.0f), // top right
         glm::vec3(0.25f, -0.25f,  -1.0f), // bottom right 
         glm::vec3(-0.25f,  0.25f,  -1.0f) , // top left  
        
        // second triangle
        glm::vec3(0.25f, -0.25f,  -1.0f), // bottom right 
        glm::vec3(-0.25f, -0.25f,  -1.0f), // bottom left
        glm::vec3(-0.25f,  0.25f, -1.0f) // top left  
    } );

   m_mesh.SetColors({ 

     glm::vec4(1.,0.,0.,1),
     glm::vec4(0.,1.,0.,1),
     glm::vec4(0.,0.,1.,1),
     
     glm::vec4(1.,0.,0.,1),
     glm::vec4(0.,1.,0.,1),
     glm::vec4(0.,0.,1.,1)
     
     }); //RGB
}

std::string ModelTransformation::getInstructions() const
{
  std::stringstream info;

  info  <<"Square mesh with gradiant colors which uses NDC coordinates. \n"
        <<"Press R to apply transformations (rotate,scale etc..). \n" 
        <<"Press C to create cloned square which shares the original mesh and non NDC transformations . \n"
        <<"To toggle back use same key buttons (R or C). \n";

  return info.str();
}

void ModelTransformation::onViewportSizeChanged(const int& width, const int& height)
{
    m_viewportSize = glm::vec2(width, height);
}

void ModelTransformation::onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods)
{
  auto angle = (float)glfwGetTime()*glm::radians(90.0f);
  if(action == GLFW_RELEASE && key == GLFW_KEY_R )
  { 
    m_startRotation = !m_startRotation;
  }
  else if(action == GLFW_RELEASE && key == GLFW_KEY_C )
  {
    m_clone = !m_clone;
  }
}

void ModelTransformation::draw()
{
    m_shader.use();  
    
    glm::mat4 mvp(1.0);  
    const auto angle = (float)glfwGetTime()*glm::radians(90.0f);
    
    if(m_startRotation)
    {
        // for square we can do with out projection matrix as the coordinates are already in NDC space
        // we can just do some animations to rotate the square. 
        // We can also Skip this transformation which draws the static square.
        auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.15, 0.15, 0));
        auto rotation = glm::rotate(translate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        auto ModelMatrix = glm::scale(rotation, glm::vec3(0.75, 1.75, 1));
        mvp =  (ModelMatrix);
    }

    m_shader.setMat4("mvp",mvp);
    m_mesh.SetColors({ 
     glm::vec4(1.,0.,0.,1) ,glm::vec4(0.,1.,0.,1),glm::vec4(0.,0.,1.,1),glm::vec4(1.,0.,0.,1) ,glm::vec4(0.,1.,0.,1),glm::vec4(0.,0.,1.,1)
     }); 
    m_mesh.Draw();
    
    if(m_clone)
    {
        // If we want to use projection matrix mapped into non NDC co-ordinate system. we need to make sure the vertices are also mapped in to projection space.
        // otherwise we would see invisible square.
        // translate it to near the centre of projection space, rotate for some animations and scale the vertices to make big enough.

      const auto focusPosition = m_viewportSize/2.f;  //always middle of the screen.
      auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(focusPosition/2.f,0));
      auto rotation = glm::rotate(translate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
      auto ModelMatrix = glm::scale(rotation, glm::vec3(150, 150, 1));

      glm::mat4 orthographicMatrix = glm::mat4(1.0f);
      orthographicMatrix = getProjectionMatrix(m_viewportSize,focusPosition,1);

      mvp = glm::mat4(1.);
      mvp =  orthographicMatrix * (ModelMatrix);

      m_shader.setMat4("mvp",mvp);
      m_mesh.SetColor(glm::vec4(1.,0.5,.5,1)); 
      m_mesh.Draw();
    }
}