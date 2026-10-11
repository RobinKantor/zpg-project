/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <vector>
#include <memory>

#include "DrawableObject.h"


class Scene
{
private:
    std::vector<std::shared_ptr<DrawableObject>> objects;

public:
    void addObject(
        std::shared_ptr<DrawableObject> object
    );

    void draw();
};