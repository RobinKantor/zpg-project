#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "ShaderProgram.h"
#include "Model.h"
#include "Scene.h"

#include "DrawableObject.h"
#include "CompositeTransformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"

class Application
{
private:
    GLFWwindow* window;

    ShaderProgram* shader1;
    ShaderProgram* shader2;

    Model* model1;
    Model* model2;
    Model* sphereModel;
    Model* treeModel;
    Model* bushModel;
    Model* loginModel;
    Model* earthModel;
    Model* sunModel;
    Model* moonModel;

    Scene* scene1;
    Scene* scene2;
    Scene* scene3;
    Scene* scene4;
    Scene* scene5;

    Scene* activeScene;

    // Transformations for scene 4
    std::shared_ptr<Translation> loginTranslation;

    std::shared_ptr<Rotation> loginRotationX;
    std::shared_ptr<Rotation> loginRotationY;
    std::shared_ptr<Rotation> loginRotationZ;

    std::shared_ptr<Scale> loginScale;

    // Transformations for scene 5
    std::shared_ptr<Rotation> sunRotation;

    std::shared_ptr<Rotation> earthOrbitRotation;
    std::shared_ptr<Rotation> earthSelfRotation;

    std::shared_ptr<Rotation> moonOrbitRotation;
    std::shared_ptr<Rotation> moonSelfRotation;

    float moveX = 0.0f;
    float moveY = 0.0f;
    float moveZ = 0.0f;

    float objectScale = 0.8f;

    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;

public:
    void initialization();
    void createShaders();
    void createModels();
    void createScenes();
    void run();
};