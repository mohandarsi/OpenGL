#include "basicTriangleDemo.h"
#include <glm/glm.hpp>

BasicTriangle::BasicTriangle():
  DemoBase("resources/base.vs", "resources/base.fs")
{

}

std::string BasicTriangle::getInstructions() const
{
  return "Basic Traingle which uses NDC coordinates. \n";
}

void BasicTriangle::init()
{
    //create Traingle
    m_mesh.SetVertices({
         glm::vec3(0.0,  0.5, -0.1), 
         glm::vec3( -0.5, -0.5, -0.1), 
         glm::vec3( 0.5, -0.5, -0.1) , 
    } );
}

void BasicTriangle::draw()
{
    m_shader.use();
    m_mesh.Draw();
}