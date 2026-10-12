/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include "Camera.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera;
class ShaderProgram {
private:
	GLuint shaderProgram;
	Camera* camera;

	GLuint createShaderFromFile(
		GLenum shaderType,
		const char* shaderFile
	);

public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile, Camera* camera);
	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::mat4& matrix);
};