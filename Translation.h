#pragma once

#include "Transformation.h"

class Translation : public Transformation
{
private:
    glm::vec3 translation;

public:
    Translation(float x, float y, float z);

    glm::mat4 getMatrix() const override;
};