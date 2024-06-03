#version 410 core

in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D ourTexture;
uniform vec4 lightColor;

void main()
{
    FragColor = texture(ourTexture, TexCoords) * lightColor;
}