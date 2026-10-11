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

public:
    DrawableObject(
        Model* model,
        ShaderProgram* shaderProgram
    );

    void setTransformation(
        std::shared_ptr<Transformation> transformation
    );

    void draw();
};