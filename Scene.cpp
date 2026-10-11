
#include "Scene.h"

void Scene::addObject(
    std::shared_ptr<DrawableObject> object
)
{
    objects.push_back(object);
}

void Scene::draw()
{
    for (const auto& object : objects)
    {
        object->draw();
    }
}