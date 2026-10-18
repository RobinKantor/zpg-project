#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 vertexColor;
out float vertexShade;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform int colorMode = 0;
uniform vec3 objectColor = vec3(1.0);

void main()
{
    vertexColor = color;

    if (colorMode == 1)
        vertexColor = objectColor;
    else if (colorMode == 2)
        vertexColor = gl_VertexID >= 36444 ? vec3(0.12, 0.55, 0.08) : vec3(0.35, 0.16, 0.06);
    else if (colorMode == 3)
        vertexColor = abs(normal);

    vertexShade = 0.3 + 0.7 * abs(normal.y);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
