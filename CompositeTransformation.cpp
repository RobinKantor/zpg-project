/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "CompositeTransformation.h"

void CompositeTransformation::addTransformation(
    std::shared_ptr<Transformation> transformation
)
{
    transformations.push_back(transformation);
}

glm::mat4 CompositeTransformation::getMatrix() const
{
    glm::mat4 matrix = glm::mat4(1.0f);

    for (const auto& transformation : transformations)
    {
        matrix = matrix * transformation->getMatrix();
    }

    return matrix;
}