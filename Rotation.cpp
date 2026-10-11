/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Rotation.h"

#include <glm/gtc/matrix_transform.hpp>

Rotation::Rotation(float angle, glm::vec3 axis)
    : angle(angle), axis(axis)
{
}

glm::mat4 Rotation::getMatrix() const
{
    return glm::rotate(
        glm::mat4(1.0f),
        angle,
        axis
    );
}

void Rotation::setAngle(float angle)
{
    this->angle = angle;
}