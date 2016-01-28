#version 330

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec4 a_color;

out vec4 color;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    color = a_color;

    gl_Position = projection * transform * vec4(a_position, 0, 1);
}