#version 330

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;
uniform bool hasTexture = false;

void main() {
    vec4 finalColor = color;

    if( hasTexture ) {
        vec4 texColor = texture2D( texture, texCoord ).rgba;
        finalColor = texColor * color;
    }

    gl_FragColor = finalColor;
}