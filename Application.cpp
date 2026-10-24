/**
 * @author Robin Kantor
 * @login KAN0310
 */

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#include "Models/sphere.h"
#include "Models/KAN0310.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/earth.h"
#include "Models/sun.h"
#include "Models/moon.h"
#include "Models/clock.h"
#include "Models/plain.h"
#include "Models/boeing737.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>


Application::~Application()
{
    delete scene1;
    delete scene2;
    delete scene3;
    delete scene4;
    delete scene5;
    delete scene6;
    delete scene7;

    delete model1;
    delete sphereModel;
    delete treeModel;
    delete bushModel;
    delete loginModel;
    delete earthModel;
    delete sunModel;
    delete moonModel;
    delete clock;
    delete groundModel;
    delete airplaneModel;

    delete shader1;
    delete shader2;
    delete clockShader;
    delete ambientShader;
    delete lambertShader;
    delete phongShader;
    delete blinnShader;

    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization()
{
    if (!glfwInit())
        std::exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress)))
    {
        std::fprintf(stderr, "GLAD initialization failed\n");
        std::exit(EXIT_FAILURE);
    }

    std::printf("OpenGL: %s\n", glGetString(GL_VERSION));
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebufferCallback(window, width, height);
}

void Application::createShaders()
{
    shader1 = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag", &camera);
    shader2 = new ShaderProgram("Shaders/basic.vert", "Shaders/basic2.frag", &camera);
    clockShader = new ShaderProgram("Shaders/clock.vert", "Shaders/basic.frag", &camera);
    ambientShader = new ShaderProgram("Shaders/light.vert", "Shaders/ambient.frag", &camera);
    lambertShader = new ShaderProgram("Shaders/light.vert", "Shaders/lambert.frag", &camera);
    phongShader = new ShaderProgram("Shaders/light.vert", "Shaders/phong.frag", &camera);
    blinnShader = new ShaderProgram("Shaders/light.vert", "Shaders/blinn.frag", &camera);
}

void Application::createModels()
{
    float points1[] = {
        -0.7f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.3f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.9f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    model1 = new Model(points1, sizeof(points1), 3, VertexFormat::PositionColor);
    sphereModel = new Model(sphere, sizeof(sphere), sizeof(sphere) / (6 * sizeof(float)));
    treeModel = new Model(tree, sizeof(tree), sizeof(tree) / (6 * sizeof(float)));
    bushModel = new Model(bushes, sizeof(bushes), sizeof(bushes) / (6 * sizeof(float)));
    loginModel = new Model(loginKAN0310, sizeof(loginKAN0310), KAN0310_VERTEX_COUNT);
    sunModel = new Model(sun, sizeof(sun), sizeof(sun) / (9 * sizeof(float)), VertexFormat::PositionColorNormal);
    earthModel = new Model(earth, sizeof(earth), sizeof(earth) / (9 * sizeof(float)), VertexFormat::PositionColorNormal);
    moonModel = new Model(moon, sizeof(moon), sizeof(moon) / (9 * sizeof(float)), VertexFormat::PositionColorNormal);
    clock = new Model(clockModel, sizeof(clockModel), static_cast<int>(vertexCount), VertexFormat::PositionNormalColor);
    groundModel = new Model(plain, sizeof(plain), 6);
    airplaneModel = new Model(boeing737, sizeof(boeing737), sizeof(boeing737) / (9 * sizeof(float)), VertexFormat::PositionColorNormal);
}
void Application::framebufferCallback(GLFWwindow* window, int width, int height)
{
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
    app->camera.resize(width, height);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_7)
        app->setScene(key - GLFW_KEY_1 + 1);
    else if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_R && app->activeSceneNumber == 4)
    {
        app->moveX = app->moveY = app->moveZ = 0.0f;
        app->rotationX = app->rotationY = app->rotationZ = 0.0f;
        app->objectScale = 0.8f;
    }
}

void Application::setScene(int number)
{
    Scene* scenes[] = { scene1, scene2, scene3, scene4, scene5, scene6, scene7 };
    activeScene = scenes[number - 1];
    activeSceneNumber = number;
    camera.setFieldOfView(60.0f);
    resetCamera();

}

void Application::resetCamera()
{
    if (activeSceneNumber == 3)
        camera.setPose(glm::vec3(0.0f, 1.7f, 23.0f), glm::half_pi<float>(), -glm::half_pi<float>());
    else if (activeSceneNumber == 6)
        camera.setPose(glm::vec3(0.0f, 0.0f, -3.0f), glm::half_pi<float>(), glm::half_pi<float>());
    else if (activeSceneNumber == 5)
        camera.setPose(glm::vec3(0.0f, 0.0f, 6.5f), glm::half_pi<float>(), -glm::half_pi<float>());
    else if (activeSceneNumber == 7)
        camera.setPose(glm::vec3(0.0f, 0.0f, 6.0f), glm::half_pi<float>(), -glm::half_pi<float>());
    else
        camera.setPose(glm::vec3(0.0f, 0.0f, 2.0f), glm::half_pi<float>(), -glm::half_pi<float>());

    firstMouse = true;
}

void Application::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    auto app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->camera.setFieldOfView(app->camera.getFieldOfView() - static_cast<float>(yOffset) * 5.0f);
}

void Application::processInput(float deltaTime)
{
    bool captured = glfwGetWindowAttrib(window, GLFW_FOCUSED)
        && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    if (captured != mouseCaptured)
    {
        mouseCaptured = captured;
        firstMouse = true;
    }

    if (mouseCaptured)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        if (!firstMouse)
            camera.rotate(static_cast<float>(x - lastMouseX), static_cast<float>(y - lastMouseY));

        firstMouse = false;
        lastMouseX = x;
        lastMouseY = y;
    }

    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
        return;

    if (activeSceneNumber == 4)
    {
        moveX += (keyPressed(GLFW_KEY_RIGHT) - keyPressed(GLFW_KEY_LEFT)) * deltaTime;
        moveY += (keyPressed(GLFW_KEY_UP) - keyPressed(GLFW_KEY_DOWN)) * deltaTime;
        moveZ += (keyPressed(GLFW_KEY_PAGE_UP) - keyPressed(GLFW_KEY_PAGE_DOWN)) * deltaTime;
        objectScale = glm::max(0.1f, objectScale + (keyPressed(GLFW_KEY_Z) - keyPressed(GLFW_KEY_X)) * deltaTime);
        rotationX += (keyPressed(GLFW_KEY_W) - keyPressed(GLFW_KEY_S)) * deltaTime;
        rotationY += (keyPressed(GLFW_KEY_A) - keyPressed(GLFW_KEY_D)) * deltaTime;
        rotationZ += (keyPressed(GLFW_KEY_Q) - keyPressed(GLFW_KEY_E)) * deltaTime;
    }
    else
    {
        glm::vec2 movement(
            keyPressed(GLFW_KEY_D) - keyPressed(GLFW_KEY_A),
            keyPressed(GLFW_KEY_W) - keyPressed(GLFW_KEY_S)
        );

        if (glm::length(movement) > 0.0f)
        {
            movement = glm::normalize(movement);
            float speed = activeSceneNumber == 3 ? 4.0f : 1.5f;
            camera.move(movement.y * speed * deltaTime, movement.x * speed * deltaTime);
        }
    }
}

bool Application::keyPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Application::updateClock()
{
    std::time_t time = std::time(nullptr);
    std::tm localTime{};
    localtime_s(&localTime, &time);

    float seconds = static_cast<float>(localTime.tm_sec);
    float minutes = localTime.tm_min + seconds / 60.0f;
    float hours = (localTime.tm_hour % 12) + minutes / 60.0f;

    clockShader->setUniform("handAngles",
        -glm::radians(seconds * 6.0f),
        -glm::radians(minutes * 6.0f),
        -glm::radians(hours * 30.0f));
}

void Application::drawLogin()
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (width <= 0 || height <= 0)
        return;

    float scale = glm::min(100.0f, width * 0.4f);
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),
        glm::vec3(width - scale - 10.0f, scale * 0.17f + 10.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, 1.0f));

    shader2->setUniform("modelMatrix", modelMatrix);
    shader2->setUniform("viewMatrix", glm::mat4(1.0f));
    shader2->setUniform("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height)));

    glDisable(GL_DEPTH_TEST);
    loginModel->draw();
    glEnable(GL_DEPTH_TEST);
    shader2->updateCamera(camera);
}

void Application::run()
{
    glEnable(GL_DEPTH_TEST);
    double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        double now = glfwGetTime();
        float deltaTime = glm::min(static_cast<float>(now - previousTime), 0.05f);
        previousTime = now;
        processInput(deltaTime);

        loginTranslation->setTranslation(moveX, moveY, moveZ);
        loginRotationX->setAngle(rotationX);
        loginRotationY->setAngle(rotationY);
        loginRotationZ->setAngle(rotationZ);
        loginScale->setScale(objectScale, objectScale, objectScale);

        float time = static_cast<float>(now);
        sunRotation->setAngle(time * 0.3f);
        earthOrbitRotation->setAngle(time * 0.5f);
        earthSelfRotation->setAngle(time * 2.0f);
        moonOrbitRotation->setAngle(time * 2.0f);
        moonSelfRotation->setAngle(time * 1.5f);
        airplaneOrbitRotation->setAngle(time * 0.25f);
        airplaneSelfRotation->setAngle(time);

        if (activeSceneNumber == 3 || activeSceneNumber == 6)
            updateClock();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        activeScene->draw();
        drawLogin();
        glfwSwapBuffers(window);
    }
}
