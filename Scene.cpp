/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Scene.h"

void Scene::addObject(std::shared_ptr<DrawableObject> object)
{
    if (nextObjectID > 255)
        return;

    object->setID(nextObjectID++);
    objects.push_back(object);
}

void Scene::removeObject(int id) 
{
    for (int i = 0; i < objects.size(); ++i) 
    {
        const auto& object = objects[i];

        if (object->getID() == id) 
        {
            objects.erase(objects.begin() + i);
            return;
        }
    }
}

void Scene::setLight(const Light& light)
{
    this->light = light;
}

void Scene::draw()
{
    if (skybox)
        skybox->draw();

    for (const auto& object : objects)
    {
        glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);
        object->draw(light);
    }
}

void Scene::setSkybox(std::shared_ptr<Skybox> skybox)
{
    this->skybox = skybox;
}
