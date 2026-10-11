#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

class ShaderProgram {
private:
	GLuint shaderProgram;

	GLuint createShaderFromFile(
		GLenum shaderType,
		const char* shaderFile
	);

public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::mat4& matrix);
};