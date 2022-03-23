#include "basicTriangleDemo.h"
#include <glm/glm.hpp>

BasicTriangle::BasicTriangle():
  DemoBase("resources/base.vs", "resources/base.fs")
{

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