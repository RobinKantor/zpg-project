/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "Camera.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Scene.h"
#include "CompositeTransformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"

class Application
{
private:
    GLFWwindow* window = nullptr;
    Camera camera;

    ShaderProgram* shader1 = nullptr;
    ShaderProgram* shader2 = nullptr;
    ShaderProgram* clockShader = nullptr;
    ShaderProgram* lightShader = nullptr;

    Model* model1 = nullptr;
    Model* sphereModel = nullptr;
    Model* treeModel = nullptr;
    Model* bushModel = nullptr;
    Model* loginModel = nullptr;
    Model* earthModel = nullptr;
    Model* sunModel = nullptr;
    Model* moonModel = nullptr;
    Model* clock = nullptr;
    Model* groundModel = nullptr;

    Scene* scene1 = nullptr;
    Scene* scene2 = nullptr;
    Scene* scene3 = nullptr;
    Scene* scene4 = nullptr;
    Scene* scene5 = nullptr;
    Scene* scene6 = nullptr;
    Scene* scene7 = nullptr;
    Scene* activeScene = nullptr;
    int activeSceneNumber = 0;

    std::shared_ptr<Translation> loginTranslation;
    std::shared_ptr<Rotation> loginRotationX;
    std::shared_ptr<Rotation> loginRotationY;
    std::shared_ptr<Rotation> loginRotationZ;
    std::shared_ptr<Scale> loginScale;

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

    bool mouseCaptured = false;
    bool firstMouse = true;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;

    void setScene(int number);
    void resetCamera();
    void processInput(float deltaTime);
    bool keyPressed(int key) const;
    void updateClock();
    static void framebufferCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    ~Application();
    void initialization();
    void createShaders();
    void createModels();
    void createScenes();
    void run();
};
