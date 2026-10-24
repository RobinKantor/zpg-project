#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    vec3 ambient = vertexColor;
    FragColor = vec4(ambient, 1.0);
}
