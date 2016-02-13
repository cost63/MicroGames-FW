#version 330

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;
uniform bool hasTexture = false;

void main()
{
    vec4 finalColor = color;

    if( hasTexture ) {
        vec4 texColor = texture2D( texture, texCoord );
        finalColor = texColor * color;
    }

    // gl_FragColor = vec4(texColor, 1);
    gl_FragColor = finalColor;
}