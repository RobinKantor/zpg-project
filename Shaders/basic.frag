#version 330 core

in vec3 vertexColor;
in float vertexShade;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexShade * vertexColor, 1.0);
}
