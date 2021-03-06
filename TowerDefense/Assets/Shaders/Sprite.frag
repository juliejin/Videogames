// Sprite.frag
// Fragment (pixel) shader for sprite rendering

#version 150

in vec2 outTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
    outColor = texture(uTexture, outTexCoord);
}
