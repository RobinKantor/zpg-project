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

#include <glm/gtc/constants.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>

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

    delete shader1;
    delete shader2;
    delete clockShader;

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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebufferCallback(window, width, height);
}

void Application::createShaders()
{
    shader1 = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag", &camera);
    shader2 = new ShaderProgram("Shaders/basic.vert", "Shaders/basic2.frag", &camera);
    clockShader = new ShaderProgram("Shaders/clock.vert", "Shaders/basic.frag", &camera);
    lightShader = new ShaderProgram("Shaders/light.vert", "Shaders/light.frag", &camera);
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
}
void Application::createScenes()
{
    scene1 = new Scene();
    scene2 = new Scene();
    scene3 = new Scene();
    scene4 = new Scene();
    scene5 = new Scene();
    scene6 = new Scene();
    scene7 = new Scene();

    auto triangle1 =
        std::make_shared<DrawableObject>(
            model1,
            shader1
        );

    auto transformation1 =
        std::make_shared<CompositeTransformation>();

    transformation1->addTransformation(
        std::make_shared<Translation>(
            0.5f,
            0.0f,
            0.0f
        )
    );

    transformation1->addTransformation(
        std::make_shared<Rotation>(
            glm::radians(45.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        )
    );

    triangle1->setTransformation(
        transformation1
    );

    scene1->addObject(
        triangle1
    );

    auto triangle2 =
        std::make_shared<DrawableObject>(
            model1,
            shader1
        );

    auto transformation2 =
        std::make_shared<CompositeTransformation>();

    transformation2->addTransformation(
        std::make_shared<Rotation>(
            glm::radians(45.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        )
    );

    transformation2->addTransformation(
        std::make_shared<Translation>(
            0.5f,
            0.0f,
            0.0f
        )
    );

    triangle2->setTransformation(
        transformation2
    );

    scene1->addObject(
        triangle2
    );
    auto scene1Login =
        std::make_shared<DrawableObject>(
            loginModel,
            shader2
        );

    auto scene1LoginTransformation =
        std::make_shared<CompositeTransformation>();

    scene1LoginTransformation->addTransformation(
        std::make_shared<Translation>(
            0.72f,
            -0.82f,
            -0.1f
        )
    );

    scene1LoginTransformation->addTransformation(
        std::make_shared<Scale>(
            0.20f,
            0.20f,
            0.20f
        )
    );

    scene1Login->setTransformation(
        scene1LoginTransformation
    );

    scene1->addObject(
        scene1Login
    );

    auto sphereObject =
        std::make_shared<DrawableObject>(
            sphereModel,
            shader1
        );

    auto sphereTransformation =
        std::make_shared<CompositeTransformation>();

    sphereTransformation->addTransformation(
        std::make_shared<Scale>(
            0.7f,
            0.7f,
            0.7f
        )
    );

    sphereObject->setColorMode(3);
    sphereObject->setTransformation(
        sphereTransformation
    );

    scene2->addObject(
        sphereObject
    );
    auto scene2Login =
        std::make_shared<DrawableObject>(
            loginModel,
            shader2
        );

    auto scene2LoginTransformation =
        std::make_shared<CompositeTransformation>();

    scene2LoginTransformation->addTransformation(
        std::make_shared<Translation>(
            0.72f,
            -0.82f,
            -0.1f
        )
    );

    scene2LoginTransformation->addTransformation(
        std::make_shared<Scale>(
            0.20f,
            0.20f,
            0.20f
        )
    );

    scene2Login->setTransformation(
        scene2LoginTransformation
    );

    scene2->addObject(
        scene2Login
    );

    auto ground = std::make_shared<DrawableObject>(groundModel, shader1);

    ground->setColor(glm::vec3(0.1f, 0.3f, 0.1f));
    ground->setTransformation(
        std::make_shared<Scale>(30.0f, 1.0f, 30.0f)
    );

    scene3->addObject(ground);

    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution<float> treePosition(-20.0f, 20.0f);
    std::uniform_real_distribution<float> treeScale(0.7f, 1.15f);
    std::uniform_real_distribution<float> rotation(0.0f, glm::two_pi<float>());

    for (int i = 0; i < 74; i++)
    {
        auto treeObject = std::make_shared<DrawableObject>(treeModel, shader1);
        auto transformation = std::make_shared<CompositeTransformation>();
        float x = treePosition(generator);
        float z = treePosition(generator);
        float scale = treeScale(generator);

        transformation->addTransformation(std::make_shared<Translation>(x, 0.0f, z));
        transformation->addTransformation(std::make_shared<Rotation>(rotation(generator), glm::vec3(0.0f, 1.0f, 0.0f)));
        transformation->addTransformation(std::make_shared<Scale>(scale, scale, scale));
        treeObject->setTransformation(transformation);
        treeObject->setColorMode(2);
        scene3->addObject(treeObject);
    }

    std::uniform_real_distribution<float> bushPosition(-23.0f, 23.0f);
    std::uniform_real_distribution<float> bushScale(1.5f, 3.0f);

    for (int i = 0; i < 15; i++)
    {
        auto bushObject = std::make_shared<DrawableObject>(bushModel, shader1);
        auto transformation = std::make_shared<CompositeTransformation>();
        float scale = bushScale(generator);

        transformation->addTransformation(std::make_shared<Translation>(bushPosition(generator), 0.0f, bushPosition(generator)));
        transformation->addTransformation(std::make_shared<Rotation>(rotation(generator), glm::vec3(0.0f, 1.0f, 0.0f)));
        transformation->addTransformation(std::make_shared<Scale>(scale, scale, scale));
        bushObject->setTransformation(transformation);
        bushObject->setColor(glm::vec3(0.16f, 0.48f, 0.08f));
        scene3->addObject(bushObject);
    }

    glm::vec3 clockPositions[] = {
        glm::vec3(-3.0f, 1.7f, 16.0f),
        glm::vec3(3.0f, 1.7f, 9.0f)
    };

    for (const glm::vec3& position : clockPositions) { 
        auto clockObject = std::make_shared<DrawableObject>(clock, clockShader);
        auto transformation = std::make_shared<CompositeTransformation>();
        
        transformation->addTransformation(
            std::make_shared<Translation>(
                position.x, position.y, position.z
            )
        );

        transformation->addTransformation(
            std::make_shared<Rotation>(
                glm::radians(180.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            )
        );

        transformation->addTransformation(
            std::make_shared<Scale>(-1.0f, 1.0f, 1.0f)
        );

        clockObject->setTransformation(transformation);
        scene3->addObject(clockObject);
    }

    auto loginObject =
        std::make_shared<DrawableObject>(
            loginModel,
            shader2
        );

    auto loginTransformation =
        std::make_shared<CompositeTransformation>();


    loginTranslation =
        std::make_shared<Translation>(
            0.0f,
            0.0f,
            0.0f
        );

    loginRotationX =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(1.0f, 0.0f, 0.0f)
        );

    loginRotationY =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    loginRotationZ =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

    loginScale =
        std::make_shared<Scale>(
            0.8f,
            0.8f,
            0.8f
        );


    loginTransformation->addTransformation(
        loginTranslation
    );

    loginTransformation->addTransformation(
        loginRotationX
    );

    loginTransformation->addTransformation(
        loginRotationY
    );

    loginTransformation->addTransformation(
        loginRotationZ
    );

    loginTransformation->addTransformation(
        loginScale
    );


    loginObject->setTransformation(
        loginTransformation
    );

    scene4->addObject(
        loginObject
    );

    auto sunObject =
        std::make_shared<DrawableObject>(
            sunModel,
            shader1
        );

    auto solarSunTransformation =
        std::make_shared<CompositeTransformation>();

    sunRotation =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    solarSunTransformation->addTransformation(
        sunRotation
    );

    solarSunTransformation->addTransformation(
        std::make_shared<Scale>(
            0.18f,
            0.18f,
            0.18f
        )
    );

    sunObject->setTransformation(
        solarSunTransformation
    );

    scene5->addObject(
        sunObject
    );

    auto earthOrbit =
        std::make_shared<CompositeTransformation>();

    earthOrbitRotation =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

    earthOrbit->addTransformation(
        earthOrbitRotation
    );

    earthOrbit->addTransformation(
        std::make_shared<Translation>(
            0.55f,
            0.0f,
            0.0f
        )
    );

    auto earthObject =
        std::make_shared<DrawableObject>(
            earthModel,
            shader1
        );

    auto earthTransformation =
        std::make_shared<CompositeTransformation>();

    earthSelfRotation =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    earthTransformation->addTransformation(
        earthOrbit
    );

    earthTransformation->addTransformation(
        earthSelfRotation
    );

    earthTransformation->addTransformation(
        std::make_shared<Scale>(
            0.08f,
            0.08f,
            0.08f
        )
    );

    earthObject->setTransformation(
        earthTransformation
    );

    scene5->addObject(
        earthObject
    );

    auto moonObject =
        std::make_shared<DrawableObject>(
            moonModel,
            shader1
        );

    auto moonTransformation =
        std::make_shared<CompositeTransformation>();

    moonOrbitRotation =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );

    auto moonOrbit =
        std::make_shared<CompositeTransformation>();

    moonOrbit->addTransformation(
        moonOrbitRotation
    );

    moonOrbit->addTransformation(
        std::make_shared<Translation>(
            0.16f,
            0.0f,
            0.0f
        )
    );

    moonSelfRotation =
        std::make_shared<Rotation>(
            0.0f,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

    moonTransformation->addTransformation(
        earthOrbit
    );

    moonTransformation->addTransformation(
        moonOrbit
    );

    moonTransformation->addTransformation(
        moonSelfRotation
    );

    moonTransformation->addTransformation(
        std::make_shared<Scale>(
            0.035f,
            0.035f,
            0.035f
        )
    );

    moonObject->setTransformation(
        moonTransformation
    );

    scene5->addObject(
        moonObject
    );


    auto clockObject = std::make_shared<DrawableObject>(clock, clockShader);
    clockObject->setTransformation(std::make_shared<Scale>(-1.0f, 1.0f, 1.0f));
    scene6->addObject(clockObject);

    glm::vec3 shperePositions[] = {
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };

    for (const glm::vec3& position : shperePositions) {
        auto sphereObject = std::make_shared<DrawableObject>(sphereModel, lightShader);
        auto transformation = std::make_shared<CompositeTransformation>();

        transformation->addTransformation(
            std::make_shared<Translation>(
                position.x, position.y, position.z
            )
        );

        transformation->addTransformation(
            std::make_shared<Scale>(
                0.5,
                0.5,
                0.5
            )
        );

        sphereObject->setTransformation(transformation);
        scene7->addObject(sphereObject);
    }

    setScene(3);
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
    resetCamera();

}

void Application::resetCamera()
{
    if (activeSceneNumber == 3)
        camera.setPose(glm::vec3(0.0f, 1.7f, 23.0f), glm::half_pi<float>(), -glm::half_pi<float>());
    else if (activeSceneNumber == 6)
        camera.setPose(glm::vec3(0.0f, 0.0f, -3.0f), glm::half_pi<float>(), glm::half_pi<float>());
    else
        camera.setPose(glm::vec3(0.0f, 0.0f, 2.0f), glm::half_pi<float>(), -glm::half_pi<float>());

    firstMouse = true;
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

        if (activeSceneNumber == 3 || activeSceneNumber == 6)
            updateClock();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        activeScene->draw();
        glfwSwapBuffers(window);
    }
}
