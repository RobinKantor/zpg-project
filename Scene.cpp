/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Scene.h"

void Scene::addObject(
    std::shared_ptr<DrawableObject> object
)
{
    objects.push_back(object);
}

void Scene::setLight(const Light& light)
{
    this->light = light;
}

void Scene::draw()
{
    for (const auto& object : objects)
    {
        object->draw(light);
    }
}