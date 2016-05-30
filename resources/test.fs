#version 330 core

in FragData 
{
    vec4 color;    
} inputData;

out vec4 color;

void main()
{
    color = inputData.color;
} 