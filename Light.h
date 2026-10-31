/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glm/glm.hpp>

class Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 color = glm::vec3(1.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};