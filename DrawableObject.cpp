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

    shaderProgram->use();
    model->draw();
}