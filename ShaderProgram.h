/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include "CameraObserver.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera;
class ShaderProgram : public CameraObserver {
private:
	GLuint shaderProgram;
	Camera* camera;

	GLuint createShaderFromFile(
		GLenum shaderType,
		const char* shaderFile
	);

public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile, Camera* camera);
	~ShaderProgram() override;
	void updateCamera(const Camera& camera) override;
	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::mat4& matrix);
};
