#include "Scale.h"

#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(float x, float y, float z)
    : scale(x, y, z)
{
}

glm::mat4 Scale::getMatrix() const
{
    return glm::scale(
        glm::mat4(1.0f),
        scale
    );
}

void Scale::setScale(
    float x,
    float y,
    float z
)
{
    scale = glm::vec3(x, y, z);
}