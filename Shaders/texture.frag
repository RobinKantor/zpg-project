#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform sampler2D samplerTexture; // 1D, 2D, 3D, samplerCube

void main ()
{
	FragColor = texture (samplerTexture, uv);
}