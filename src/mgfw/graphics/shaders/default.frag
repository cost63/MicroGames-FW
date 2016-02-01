#version 330

in vec4 color;
in vec2 texCoord;

uniform sampler2D texture;
uniform bool hasTexture = false;

void main()
{
    vec4 finalColor = color;

    // if( hasTexture ) {
    //     vec3 texColor = texture2D( texture, texCoord ).rgb;
    //     finalColor = vec4( color.rgb * texColor, color.a );
    // }

    // gl_FragColor = vec4(texColor, 1);
    gl_FragColor = finalColor;
}