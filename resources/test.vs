#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 fsColor;

void main() 
{
    fsColor = color;
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}