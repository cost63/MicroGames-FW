#version 330

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 projection;
uniform mat4 transform;

void main() {
    color = a_color;
    texCoord = a_texCoord;

    gl_Position = projection * transform * vec4(a_position, 0, 1);
}