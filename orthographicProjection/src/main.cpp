#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "mesh.h"
#include "camera2d.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void setupViewport(int width, int height);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
auto fullscreen = false;  // to control fullscreen

glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

void createTriangle2D(Mesh& triangleMesh)
{
    triangleMesh.SetVertices( {
        glm::vec3(10.0f, 150.0f, -1.0f), // left  
        glm::vec3(400.f, 150.0f, -1.0f), // right 
        glm::vec3(200.0f, 20.0f, -1.0f)  // top   
    } );

   triangleMesh.SetColors({ glm::vec4(1.,0.,0.,1) ,glm::vec4(0.,1.,0.,1),glm::vec4(0.,0.,1.,1)}); //RGB
}

void createSquare2D(Mesh& squareMesh)
{
    squareMesh.SetVertices({
          // first half triangle
         glm::vec3(0.25f,  0.25f, -1.0f), // top right
         glm::vec3(0.25f, -0.25f,  -1.0f), // bottom right 
         glm::vec3(-0.25f,  0.25f,  -1.0f) , // top left  
        
        // second triangle
        glm::vec3(0.25f, -0.25f,  -1.0f), // bottom right 
        glm::vec3(-0.25f, -0.25f,  -1.0f), // bottom left
        glm::vec3(-0.25f,  0.25f, -1.0f) // top left  
    } );

     squareMesh.SetColor(glm::vec4(0.,1.,0.,1)); //GREEN
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", fullscreen?glfwGetPrimaryMonitor():nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------

    Shader ourShader("resources/base.vs", "resources/base.fs");
 
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // We use different co-ordinates for traingle and mesh and maniuplate to disply
    // in window by using transofrmations. 
    // ------------------------------------------------------------------
    Mesh triangleMesh;  createTriangle2D(triangleMesh);
    

    Mesh squareMesh; createSquare2D(squareMesh);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   
    setupViewport(SCR_WIDTH,SCR_HEIGHT);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // for traingle we need to map vertices into NDC, for this we need projection matrix.
        ourShader.use();
        glm::mat4 mvp =  ProjectionMatrix;
        ourShader.setMat4("mvp",mvp);
        triangleMesh.Draw();


        // for square we can do with out projection matrix as the coordinates are already in NDC space
        // we can just do some animations to rotate the square. 
        // We can also Skip this transformation which draws the static square.

        auto angle = (float)glfwGetTime()*glm::radians(90.0f);

        auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.15, 0.15, 0));
        auto rotation = glm::rotate(translate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        auto ModelMatrix = glm::scale(rotation, glm::vec3(0.25, 0.25, 1));

        mvp = glm::mat4(1.0);
        mvp =  (ModelMatrix);
        ourShader.setMat4("mvp", mvp);
        squareMesh.SetColor(glm::vec4(0.,1.,0.,1)); //GREEN
        squareMesh.Draw();


        // If we want to use projection matrix we need to make sure the vertices are mapped to projection corodinates otherwise we would see invisible square.
        // translate it to near the centre of projection space, rotate for some animations and scale the vertices to make big enough.
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(SCR_WIDTH / 2, SCR_HEIGHT / 2, 0));
        rotation = glm::rotate(translate, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::scale(rotation, glm::vec3(100, 100, 1));

        mvp = glm::mat4(1.0);
        mvp =  ProjectionMatrix * (ModelMatrix);
        ourShader.setMat4("mvp", mvp);
        squareMesh.SetColor(glm::vec4(0.,0.,1.,1)); //BLUE
        squareMesh.Draw();


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    setupViewport(width, height);
}


// Set viewport for a provided width and height
void setupViewport(int width, int height)
{
    glViewport(0, 0, width, height);
    glm::vec2 viewportSize(width,height);
    //2D- set focus position as middle of the screen.
    Camera2D camera2d(viewportSize,viewportSize/2.f,1.2f);
    ProjectionMatrix = camera2d.getProjectionMatrix();
}