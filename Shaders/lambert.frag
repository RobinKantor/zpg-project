#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 lightPosition = vec3(0.0);
uniform vec3 lightColor = vec3(1.0);

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 ambient = 0.1 * vertexColor;
    vec3 diffuse = diff * vertexColor * lightColor;
    FragColor = vec4(ambient + diffuse, 1.0);
}
