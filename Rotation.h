#pragma once

#include "Transformation.h"

class Rotation : public Transformation
{
private:
    float angle;
    glm::vec3 axis;

public:
    Rotation(float angle, glm::vec3 axis);

    glm::mat4 getMatrix() const override;
};