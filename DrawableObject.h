/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Material.h"

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;
    Material material;

    std::shared_ptr<Transformation> transformation;
    int colorMode = 0;
    glm::vec3 color = glm::vec3(1.0f);

public:
    DrawableObject(
        Model* model,
        ShaderProgram* shaderProgram
    );

    void setTransformation(
        std::shared_ptr<Transformation> transformation
    );

    void draw(const Light& light);
    void setColor(const glm::vec3& color);
    void setColorMode(int mode);
    void setMaterial(const Material& material);
};
