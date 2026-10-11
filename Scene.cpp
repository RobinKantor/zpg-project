#include "Scene.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Scene::addObject(
    Model* model,
    ShaderProgram* shader,
    float x,
    float y,
    float z,
    float scale,
    float rotationX,
    float rotationY,
    float rotationZ
)
{
    SceneObject object;

    object.model = model;
    object.shader = shader;

    object.x = x;
    object.y = y;
    object.z = z;

    object.scale = scale;

    object.rotationX = rotationX;
    object.rotationY = rotationY;
    object.rotationZ = rotationZ;

    objects.push_back(object);
}

void Scene::setObjectTransform(
    int index,
    float x,
    float y,
    float z,
    float scale,
    float rotationX,
    float rotationY,
    float rotationZ
)
{
    if (index < 0 || index >= objects.size())
        return;

    objects[index].x = x;
    objects[index].y = y;
    objects[index].z = z;

    objects[index].scale = scale;

    objects[index].rotationX = rotationX;
    objects[index].rotationY = rotationY;
    objects[index].rotationZ = rotationZ;
}


void Scene::draw()
{
    for (SceneObject& object : objects)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        modelMatrix = glm::translate(
            modelMatrix,
            glm::vec3(object.x, object.y, object.z)
        );

        modelMatrix = glm::rotate(
            modelMatrix,
            object.rotationX,
            glm::vec3(1.0f, 0.0f, 0.0f)
        );

        modelMatrix = glm::rotate(
            modelMatrix,
            object.rotationY,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        modelMatrix = glm::rotate(
            modelMatrix,
            object.rotationZ,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

        modelMatrix = glm::scale(
            modelMatrix,
            glm::vec3(object.scale)
        );

        object.shader->setUniform(
            "modelMatrix",
            modelMatrix
        );

        object.shader->use();
        object.model->draw();
    }
}