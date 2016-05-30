#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out FragData
{
    vec4 color;
} fragData;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    fragData.color = color;
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
}