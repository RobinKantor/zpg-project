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

void DrawableObject::draw(const Light& light)
{
    shaderProgram->setLight(light);

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

    shaderProgram->setUniform("material.ambient",
        material.ambient.x, material.ambient.y, material.ambient.z);

    shaderProgram->setUniform("material.diffuse",
        material.diffuse.x, material.diffuse.y, material.diffuse.z);

    shaderProgram->setUniform("material.specular",
        material.specular.x, material.specular.y, material.specular.z);

    shaderProgram->setUniform("material.shininess", material.shininess);

    if (texture)
    {
        texture->bind();
        shaderProgram->setUniform("samplerTexture", 0);
    }

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

void DrawableObject::setMaterial(const Material& material)
{
    this->material = material;
}

void DrawableObject::setTexture(std::shared_ptr<Texture> texture)
{
    this->texture = texture;
}
