#version 330 core
layout (location = 0) in vec3 position;

//model view projection matrix which gets from the program.
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0f);
} 