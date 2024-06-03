#version 410 core

uniform vec4 ourColor;
uniform vec4 lightColor;
out vec4 FragColor;

void main()
{
    FragColor = ourColor * lightColor;
}