#pragma once

#include "Transformation.h"

class Scale : public Transformation
{
private:
    glm::vec3 scale;

public:
    Scale(float x, float y, float z);

    glm::mat4 getMatrix() const override;
    void setScale(float x, float y, float z);
};