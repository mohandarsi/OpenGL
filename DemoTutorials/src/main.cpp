#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include <string>

#include "basicTriangleDemo.h"
#include "orthographicProjection.h"
#include "orthographicProjectionNDC.h"
#include "modelTransformation.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void setupViewport(int width, int height);
static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
auto fullscreen = false;  // to control fullscreen

glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

std::unique_ptr<DemoBase> g_globalDemoObject = nullptr;

int ParseProgramOptions()
{
    
    std::cout << std::endl;
    std::cout << "1  -- Basic Triangle" << std::endl;
    std::cout << "2  -- Orthographic projection - NDC space" << std::endl;
    std::cout << "3  -- Orthographic projection - Non NDC space" << std::endl;
    std::cout << "4  -- Model Transformations" << std::endl;

    int number;
    
    std::cout << std::endl << "Enter the demo number to run : ";
    std::cin >> number;

    return number;
}

std::unique_ptr<DemoBase> LaunchApplication(const int& option)
{
    switch (option)
    {
    case 1 :
        return std::make_unique<BasicTriangle>();
        break;
    case 2 :
        return std::make_unique<OrthographicProjectionNDC>();
        break;
    case 3 :
        return std::make_unique<OrthographicProjection>();
        break;
    case 4 :
        return std::make_unique<ModelTransformation>();
        break;

    default:
        break;
    }
    return nullptr;
}

int main()
{
    const auto option=  ParseProgramOptions();

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

     // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Demo OpenGL", fullscreen?glfwGetPrimaryMonitor():nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
  
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, KeyCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    g_globalDemoObject = LaunchApplication(option);

    if(g_globalDemoObject == nullptr)
    {
        std::cout << "Failed to launch application" << std::endl;
        glfwTerminate();
        return -1;
    }

    g_globalDemoObject->init();
   
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        
        g_globalDemoObject->draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    g_globalDemoObject.reset();

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
    if(g_globalDemoObject) g_globalDemoObject->onViewportSizeChanged(width, height);
}

// GLFW3: Keyboard callback
static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(g_globalDemoObject) g_globalDemoObject->onKeyPressed(key, scancode, action, mods);
}