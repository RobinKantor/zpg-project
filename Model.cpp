/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Model.h"

Model::Model(const float* points, int size, int vertexCount, VertexFormat format)
    : vertexCount(vertexCount)
{
    bool hasColor = format != VertexFormat::PositionNormal;
    bool hasNormal = format != VertexFormat::PositionColor;
    int valuesPerVertex = hasColor && hasNormal ? 9 : 6;
    int colorOffset = format == VertexFormat::PositionNormalColor ? 6 : 3;
    int normalOffset = format == VertexFormat::PositionColorNormal ? 6 : 3;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, valuesPerVertex * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    if (hasColor)
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, valuesPerVertex * sizeof(float),
            reinterpret_cast<void*>(colorOffset * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    else
        glVertexAttrib3f(1, 1.0f, 1.0f, 1.0f);

    if (hasNormal)
    {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, valuesPerVertex * sizeof(float),
            reinterpret_cast<void*>(normalOffset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else
        glVertexAttrib3f(2, 0.0f, 1.0f, 0.0f);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::~Model()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}