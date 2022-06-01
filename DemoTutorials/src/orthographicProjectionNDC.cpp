#include "orthographicProjectionNDC.h"

#include <GLFW/glfw3.h> // for GLFW_KEY_SPACE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>      // std::stringstream

OrthographicProjectionNDC::OrthographicProjectionNDC():
  DemoBase("resources/baseColor.vs", "resources/baseColor.fs"),
  m_mvp(glm::mat4(1.))
{

}

void OrthographicProjectionNDC::init()
{
    //create Traingle
    m_mesh.SetVertices({
         // The blue triangle in front
         glm::vec3(0.0,  0.5, -0.1), 
         glm::vec3( -0.5, -0.5, -0.1), 
         glm::vec3( 0.5, -0.5, -0.1) , 

         // The red triangle behind
         glm::vec3( 0.5,  0.4, -0.5), 
         glm::vec3( -0.5,  0.4, -0.5), 
         glm::vec3(  0.0, -0.6, -0.5) 
    } );

     m_mesh.SetColors({ 
       // The blue triangle in front
         glm::vec4(0.0, 0.0, 1.0,1.) ,
         glm::vec4(0.0, 0.0, 1.0,1.),
         glm::vec4(1.0, 1.0, 0.0,1.),

        // The red triangle behind
         glm::vec4(1.0, 1.0, 0.0,1.) ,
         glm::vec4(1.0, 0.0, 0.0,1.),
         glm::vec4(1.0, 0.0, 0.0,1.)
        });
}

std::string OrthographicProjectionNDC::getInstructions() const
{
  std::stringstream info;
  
  info  <<"Blue triangle in top and red triangle in back. Both are in NDC space.\n"
        <<"By default OpenGL is a Left handed cooordinate system. if its right handed(Negative Z-Axis points into screen),\
         Red traingle(Z= -0.5) should be back of Blue traingle(Z= -0.1). \n"
        <<"Press any key to apply projection(switches to right hand) which switches the traingle \n"
        <<"Press any key to toggle. \n";
        
  return info.str();
}

void OrthographicProjectionNDC::onKeyPressed(const int& key, const int& scancode, const int& action, const int& mods)
{

  if(action != GLFW_RELEASE) return;

  const auto isIdentity =  (glm::mat4(1.) == m_mvp);
  
  if(isIdentity)
  {
    m_mvp =  glm::mat4(1.);

    auto cameraTransformation =  glm::mat4(1.);
    cameraTransformation = glm::lookAt(glm::vec3(0,0,3.), glm::vec3(0,0,0), glm::vec3(0.25,0.5,0)); //To make little rotation on the model

    auto orthographicProjection =  glm::mat4(1.);
    orthographicProjection = glm::ortho(-1.f, 1.f, -1.f, 1.f, .1f, 4.f);  // here far plane is 4.f as we placed camera at 3.

    m_mvp =  orthographicProjection * cameraTransformation; // Set the viewing volume
  }
  else
  {
    m_mvp =  glm::mat4(1.);
  }
}

void OrthographicProjectionNDC::draw()
{
    m_shader.use();  
    m_shader.setMat4("mvp",m_mvp);
    m_mesh.Draw();
}