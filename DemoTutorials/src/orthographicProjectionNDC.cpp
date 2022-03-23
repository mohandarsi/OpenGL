#include "orthographicProjectionNDC.h"

#include <GLFW/glfw3.h> // for GLFW_KEY_SPACE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
      
  std::cout<< "OpenGL is Left handed cooordinate system. if its right handed(Negative Z-Axis points into screen) , Blue traingle (Z= -0.1) \
  should be front and Red traingle(Z= -0.5) should be back of Blue traingle. \
  But this is not the case. It is because we are not applying any projection. The traingle itslef visible because the \
  coordinates are already in NDC space."<< std::endl;

  std::cout<< "Press any key to toggle." << std::endl;

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