#version 330

in vec4 color;

void main()
{
    gl_FragColor = color;
    // gl_FragColor = vec4(1, 1, 1, 1);
}