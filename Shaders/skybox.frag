#version 330 core

in vec3 texCoord;
out vec4 FragColor;

uniform samplerCube skyboxTexture;

void main()
{
    FragColor = texture(skyboxTexture, texCoord);
}
