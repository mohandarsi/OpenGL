#include "shader.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    auto vertShader = createShader(vertexPath,GL_VERTEX_SHADER);
    auto fragShader = createShader(fragmentPath,GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessery
    glDetachShader(ID, vertShader);
    glDetachShader(ID, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

GLuint Shader::createShader(const char* filePath, GLenum shaderType)
{
    // Load and compile shader
    GLuint shader = glCreateShader(shaderType);
    std::string shaderStr;
    std::ifstream shaderFile;
        // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        // convert stream into string
        shaderStr = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    const char* shaderSrc = shaderStr.c_str();
    glShaderSource(shader, 1, &shaderSrc, 0); // Load shader from source file
    glCompileShader(shader);
    // Check for shader compile errors
    checkCompileErrors(shader,"SHADER");

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    std::unique_ptr<char[]> infoLog;
    GLint logLength = 0;
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            infoLog = std::make_unique<char[]>(logLength);
            glGetShaderInfoLog(shader, logLength, 0, infoLog.get());

        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            infoLog = std::make_unique<char[]>(logLength);
            glGetProgramInfoLog(shader, logLength, 0, infoLog.get());
        }
    }

    if(infoLog)
    {
        std::cerr << "Error: Could not compile shader\n" << infoLog << std::endl;
    }
}