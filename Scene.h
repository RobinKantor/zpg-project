#pragma once

#include <vector>

#include "Model.h"
#include "ShaderProgram.h"


class Scene
{
private:
    std::vector<DrawableObject> objects;

public:
    void addObject(
        Model* model,
        ShaderProgram* shader,
        float x = 0.0f,
        float y = 0.0f,
        float z = 0.0f,
        float scale = 1.0f,
        float rotationX = 0.0f,
        float rotationY = 0.0f,
        float rotationZ = 0.0f
    );

    void setObjectTransform(
        int index,
        float x,
        float y,
        float z,
        float scale,
        float rotationX,
        float rotationY,
        float rotationZ
    );

    void draw();
};