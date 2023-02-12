#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 InColour;

out vec4 Colour;

uniform mat4 gWorldViewProjection;

void main()
{
    gl_Position = gWorldViewProjection * vec4(Position, 1.0);
    Colour      = vec4(InColour, 1.0);
}