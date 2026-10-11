/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Translation.h"

#include <glm/gtc/matrix_transform.hpp>

Translation::Translation(float x, float y, float z)
    : translation(x, y, z)
{
}

glm::mat4 Translation::getMatrix() const
{
    return glm::translate(
        glm::mat4(1.0f),
        translation
    );
}

void Translation::setTranslation(
    float x,
    float y,
    float z
)
{
    translation = glm::vec3(x, y, z);
}