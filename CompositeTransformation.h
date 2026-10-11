/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <vector>
#include <memory>

#include "Transformation.h"

class CompositeTransformation : public Transformation
{
private:
    std::vector<std::shared_ptr<Transformation>> transformations;

public:
    void addTransformation(
        std::shared_ptr<Transformation> transformation
    );

    glm::mat4 getMatrix() const override;
};