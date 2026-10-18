/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <memory>

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;

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

    void draw();
    void setColor(const glm::vec3& color);
    void setColorMode(int mode);
};
