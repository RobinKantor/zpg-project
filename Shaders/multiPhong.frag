#version 330 core

#define MAX_LIGHTS 4

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

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

struct Light
{
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

uniform Material material;
uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform vec3 cameraPosition;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPosition - worldPosition);

    vec3 result = material.ambient * vertexColor;

    for (int i = 0; i < numberOfLights; i++)
    {
        vec3 lightPos = lights[i].position.xyz;
        float distance = length(lightPos - worldPosition);
        float att = clamp(1.0 / (constant + linear * distance + quadratic * (distance * distance)), 0.0, 1.0);

        vec3 lightDir = normalize(lightPos - worldPosition);
        float diff = max(dot(normal, lightDir), 0.0);

        float spec = 0.0;
        if (diff > 0.0)
        {
            vec3 reflectDir = reflect(-lightDir, normal);
            spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        }

        vec3 diffuse = material.diffuse * diff * vertexColor * lights[i].diffuse.rgb * att;
        vec3 specular = material.specular * spec * lights[i].specular.rgb * att;

        result += diffuse + specular;
    }

    FragColor = vec4(result, 1.0);
}
