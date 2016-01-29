#version 330

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;

void main()
{
    vec3 texColor = texture2D( texture, texCoord ).rgb;

    gl_FragColor = vec4(texColor, 1);
    // gl_FragColor = vec4( color.rgb * texColor, color.a );
}