#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 vertexColor;
out float vertexShade;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform vec3 handAngles;

void main()
{
    float angle = 0.0;

    if (color == vec3(0.0, 1.0, 0.0))
        angle = handAngles.y;
    else if (color == vec3(0.0, 0.0, 1.0))
        angle = handAngles.z;
    else if (color == vec3(1.0, 0.0, 0.0))
        angle = handAngles.x;

    float c = cos(angle);
    float s = sin(angle);
    mat3 rotation = mat3(c, s, 0.0, -s, c, 0.0, 0.0, 0.0, 1.0);

    vertexShade = 1.0;
    vertexColor = color;
    if (color == vec3(1.0, 1.0, 0.0))
        vertexColor = vec3(5.0, 195.0, 222.0) / 255.0;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(rotation * position, 1.0);
}
