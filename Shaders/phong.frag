#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

uniform vec3 lightPosition = vec3(0.0);
uniform vec3 lightColor = vec3(1.0);
uniform vec3 cameraPosition;

out vec4 FragColor;

uniform float constant = 1.0;
uniform float linear = 0.09;
uniform float quadratic = 0.032;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main()
{
    float distance = length(lightPosition - worldPosition);

    float att = clamp(1.0 / (constant + linear * distance + quadratic * (distance * distance)), 0.0, 1.0);

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 viewDir = normalize(cameraPosition - worldPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    float spec = 0.0;
    if (diff > 0.0)
    {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }

    vec3 ambient = material.ambient * vertexColor;
    vec3 diffuse = material.diffuse * diff * vertexColor * lightColor * att;
    vec3 specular = material.specular * spec * lightColor * att;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
