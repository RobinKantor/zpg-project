/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glm/glm.hpp>

class Transformation
{
public:
    virtual glm::mat4 getMatrix() const = 0;

    virtual ~Transformation() = default;
};