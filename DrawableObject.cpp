/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "DrawableObject.h"

DrawableObject::DrawableObject(
    Model* model,
    ShaderProgram* shaderProgram
)
{
    this->model = model;
    this->shaderProgram = shaderProgram;
}

void DrawableObject::setTransformation(
    std::shared_ptr<Transformation> transformation
)
{
    this->transformation = transformation;
}

void DrawableObject::draw()
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    if (transformation)
    {
        modelMatrix = transformation->getMatrix();
    }

    shaderProgram->setUniform(
        "modelMatrix",
        modelMatrix
    );

    shaderProgram->setUniform("colorMode", colorMode);
    shaderProgram->setUniform("objectColor", color.x, color.y, color.z);

    shaderProgram->use();
    model->draw();
}

void DrawableObject::setColor(const glm::vec3& color)
{
    this->color = color;
    colorMode = 1;
}

void DrawableObject::setColorMode(int mode)
{
    colorMode = mode;
}
