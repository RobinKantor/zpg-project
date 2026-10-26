#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 lightPosition = vec3(0.0);
uniform vec3 lightColor = vec3(1.0);
uniform vec3 cameraPosition;

const float constant = 1.0;
const float linear = 0.09;
const float quadratic = 0.032;

out vec4 FragColor;

void main()
{
    float distance = length(lightPosition - worldPosition);

    float att = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    float spec = 0.0;
    if (diff > 0.0)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    }

    vec3 ambient = 0.1 * vertexColor;
    vec3 diffuse = diff * vertexColor * lightColor * att;
    vec3 specular = 0.5 * spec * lightColor * att;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
