#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

//model view projection matrix which gets from the program.
uniform mat4 mvp;
out vec4 fragColor;

void main()
{
    gl_Position = mvp * vec4(position, 1.0f);
    fragColor = color;
} 