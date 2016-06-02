#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

layout (std140) uniform Camera
{
    mat4 projection;
    mat4 view;
} camera;

out FragData
{
    vec4 color;
} fragData;

uniform mat4 model;

void main() 
{
    fragData.color = color;
    gl_Position = camera.projection * camera.view * model * vec4(position.x, position.y, position.z, 1.0);
}