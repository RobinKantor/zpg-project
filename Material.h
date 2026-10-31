/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glm/glm.hpp>

class Material
{
public:
    glm::vec3 ambient = glm::vec3(0.02f);
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(0.2f);

    float shininess = 32.0f;
};