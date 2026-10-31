#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform int colorMode = 0;
uniform vec3 objectColor = vec3(1.0);

void main()
{
    vec4 world = modelMatrix * vec4(position, 1.0);
    worldPosition = world.xyz / world.w;
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNormal = normalize(normalMatrix * normal);

    if (colorMode == 1)
    {
        vertexColor = objectColor;
    }
    else if (colorMode == 2)
    {
        if (gl_VertexID >= 36444)
            vertexColor = vec3(0.12, 0.55, 0.08);
        else
            vertexColor = vec3(0.35, 0.16, 0.06);
    }
    else
    {
        vertexColor = color;
    }

    gl_Position = projectionMatrix * viewMatrix * world;
}
