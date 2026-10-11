/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glad/gl.h>

class Model {
private:
	GLuint VBO;
	GLuint VAO;
	GLsizei vertexCount;

public:
	Model(
		const float* points,
		int size,
		int vertexCount,
		int valuesPerVertex = 6
	);

	void draw();
};