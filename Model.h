#pragma once

#include <glad/gl.h>

class Model {
private:
	GLuint VBO;
	GLuint VAO;
	GLsizei vertexCount;

public:
	Model(
		const float* data,
		size_t dataSize,
		GLsizei vertexCount
	);

	void draw();
};