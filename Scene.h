/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <vector>
#include <memory>

#include "DrawableObject.h"
#include "Light.h"


class Scene
{
private:
    std::vector<std::shared_ptr<DrawableObject>> objects;
    Light light;

public:
    void addObject(
        std::shared_ptr<DrawableObject> object
    );
    void setLight(const Light& light);

    void draw();
};