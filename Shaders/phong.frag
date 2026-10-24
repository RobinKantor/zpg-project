#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 lightPosition = vec3(0.0);
uniform vec3 lightColor = vec3(1.0);
uniform vec3 cameraPosition;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    float spec = 0.0;
    if (diff > 0.0)
    {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    }

    vec3 ambient = 0.1 * vertexColor;
    vec3 diffuse = diff * vertexColor * lightColor;
    vec3 specular = 0.5 * spec * lightColor;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
