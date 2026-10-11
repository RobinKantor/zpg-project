/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Model.h"


Model::Model(
    const float* points,
    int size,
    int vertexCount,
    int valuesPerVertex
)
{
    this->vertexCount = vertexCount;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        points,
        GL_STATIC_DRAW
    );

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        valuesPerVertex * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // Color / second vec3
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        valuesPerVertex * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    // Normal - only models with 9 values per vertex
    if (valuesPerVertex >= 9)
    {
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            valuesPerVertex * sizeof(float),
            (void*)(6 * sizeof(float))
        );

        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(0);
}

void Model::draw() {
	glBindVertexArray(VAO);

	// Draw a triangles
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}