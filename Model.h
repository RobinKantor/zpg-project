/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glad/gl.h>

enum class VertexFormat
{
	PositionColor,
	PositionNormal,
	PositionColorNormal,
	PositionNormalColor
};

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
		VertexFormat format = VertexFormat::PositionNormal
	);
	~Model();

	void draw();
};
