/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Application.h"

#include <glm/gtc/constants.hpp>
#include <random>

void Application::createScenes()
{
    scene1 = new Scene();
    scene2 = new Scene();
    scene3 = new Scene();
    scene4 = new Scene();
    scene5 = new Scene();
    scene6 = new Scene();
    scene7 = new Scene();

    createTransformationScene();
    createSphereScene();
    createForestScene();
    createLoginScene();
    createSolarScene();
    createClockScene();
    createLightingScene();
    setScene(3);
}

void Application::createTransformationScene()
{
    auto first = std::make_shared<DrawableObject>(model1, shader1);
    auto firstTransformation = std::make_shared<CompositeTransformation>();
    firstTransformation->addTransformation(std::make_shared<Translation>(0.5f, 0.0f, 0.0f));
    firstTransformation->addTransformation(std::make_shared<Rotation>(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    first->setTransformation(firstTransformation);
    scene1->addObject(first);

    auto second = std::make_shared<DrawableObject>(model1, shader1);
    auto secondTransformation = std::make_shared<CompositeTransformation>();
    secondTransformation->addTransformation(std::make_shared<Rotation>(glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    secondTransformation->addTransformation(std::make_shared<Translation>(0.5f, 0.0f, 0.0f));
    second->setTransformation(secondTransformation);
    scene1->addObject(second);
}

void Application::createSphereScene()
{
    auto sphere = std::make_shared<DrawableObject>(sphereModel, shader1);
    sphere->setColorMode(3);
    sphere->setTransformation(std::make_shared<Scale>(0.7f, 0.7f, 0.7f));
    scene2->addObject(sphere);
}

void Application::createForestScene()
{
    auto ground = std::make_shared<DrawableObject>(groundModel, shader1);
    ground->setColor(glm::vec3(0.1f, 0.3f, 0.1f));
    ground->setTransformation(std::make_shared<Scale>(30.0f, 1.0f, 30.0f));
    scene3->addObject(ground);

    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution<float> treePosition(-20.0f, 20.0f);
    std::uniform_real_distribution<float> treeScale(0.7f, 1.15f);
    std::uniform_real_distribution<float> rotation(0.0f, glm::two_pi<float>());

    for (int i = 0; i < 74; i++)
    {
        auto tree = std::make_shared<DrawableObject>(treeModel, shader1);
        auto transformation = std::make_shared<CompositeTransformation>();
        float x = treePosition(generator);
        float z = treePosition(generator);
        float scale = treeScale(generator);
        transformation->addTransformation(std::make_shared<Translation>(x, 0.0f, z));
        transformation->addTransformation(std::make_shared<Rotation>(rotation(generator), glm::vec3(0.0f, 1.0f, 0.0f)));
        transformation->addTransformation(std::make_shared<Scale>(scale, scale, scale));
        tree->setTransformation(transformation);
        tree->setColorMode(2);
        scene3->addObject(tree);
    }

    std::uniform_real_distribution<float> bushPosition(-23.0f, 23.0f);
    std::uniform_real_distribution<float> bushScale(1.5f, 3.0f);

    for (int i = 0; i < 15; i++)
    {
        auto bush = std::make_shared<DrawableObject>(bushModel, shader1);
        auto transformation = std::make_shared<CompositeTransformation>();
        float scale = bushScale(generator);
        transformation->addTransformation(std::make_shared<Translation>(bushPosition(generator), 0.0f, bushPosition(generator)));
        transformation->addTransformation(std::make_shared<Rotation>(rotation(generator), glm::vec3(0.0f, 1.0f, 0.0f)));
        transformation->addTransformation(std::make_shared<Scale>(scale, scale, scale));
        bush->setTransformation(transformation);
        bush->setColor(glm::vec3(0.16f, 0.48f, 0.08f));
        scene3->addObject(bush);
    }

    glm::vec3 positions[] = {
        glm::vec3(-3.0f, 1.7f, 16.0f),
        glm::vec3(3.0f, 1.7f, 9.0f)
    };

    for (const glm::vec3& position : positions)
    {
        auto object = std::make_shared<DrawableObject>(clock, clockShader);
        auto transformation = std::make_shared<CompositeTransformation>();
        transformation->addTransformation(std::make_shared<Translation>(position.x, position.y, position.z));
        transformation->addTransformation(std::make_shared<Rotation>(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
        transformation->addTransformation(std::make_shared<Scale>(-1.0f, 1.0f, 1.0f));
        object->setTransformation(transformation);
        scene3->addObject(object);
    }
}

void Application::createLoginScene()
{
    auto object = std::make_shared<DrawableObject>(loginModel, shader2);
    auto transformation = std::make_shared<CompositeTransformation>();

    loginTranslation = std::make_shared<Translation>(0.0f, 0.0f, 0.0f);
    loginRotationX = std::make_shared<Rotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    loginRotationY = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    loginRotationZ = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    loginScale = std::make_shared<Scale>(0.8f, 0.8f, 0.8f);

    transformation->addTransformation(loginTranslation);
    transformation->addTransformation(loginRotationX);
    transformation->addTransformation(loginRotationY);
    transformation->addTransformation(loginRotationZ);
    transformation->addTransformation(loginScale);
    object->setTransformation(transformation);
    scene4->addObject(object);
}

void Application::createSolarScene()
{
    auto sun = std::make_shared<DrawableObject>(sunModel, ambientShader);
    auto sunTransformation = std::make_shared<CompositeTransformation>();
    sunRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    sunTransformation->addTransformation(sunRotation);
    sunTransformation->addTransformation(std::make_shared<Scale>(0.45f, 0.45f, 0.45f));
    sun->setTransformation(sunTransformation);
    scene5->addObject(sun);

    auto earthOrbit = std::make_shared<CompositeTransformation>();
    earthOrbitRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    earthOrbit->addTransformation(earthOrbitRotation);
    earthOrbit->addTransformation(std::make_shared<Translation>(1.4f, 0.0f, 0.0f));

    auto earth = std::make_shared<DrawableObject>(earthModel, phongShader);
    auto earthTransformation = std::make_shared<CompositeTransformation>();
    earthSelfRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    earthTransformation->addTransformation(earthOrbit);
    earthTransformation->addTransformation(earthSelfRotation);
    earthTransformation->addTransformation(std::make_shared<Scale>(0.22f, 0.22f, 0.22f));
    earth->setTransformation(earthTransformation);
    scene5->addObject(earth);

    auto moonOrbit = std::make_shared<CompositeTransformation>();
    moonOrbitRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    moonOrbit->addTransformation(moonOrbitRotation);
    moonOrbit->addTransformation(std::make_shared<Translation>(0.42f, 0.0f, 0.0f));

    auto moon = std::make_shared<DrawableObject>(moonModel, blinnShader);
    auto moonTransformation = std::make_shared<CompositeTransformation>();
    moonSelfRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    moonTransformation->addTransformation(earthOrbit);
    moonTransformation->addTransformation(moonOrbit);
    moonTransformation->addTransformation(moonSelfRotation);
    moonTransformation->addTransformation(std::make_shared<Scale>(0.09f, 0.09f, 0.09f));
    moon->setTransformation(moonTransformation);
    scene5->addObject(moon);

    auto airplane = std::make_shared<DrawableObject>(airplaneModel, phongShader);
    auto airplaneTransformation = std::make_shared<CompositeTransformation>();
    airplaneOrbitRotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    airplaneSelfRotation = std::make_shared<Rotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    airplaneTransformation->addTransformation(airplaneOrbitRotation);
    airplaneTransformation->addTransformation(std::make_shared<Translation>(2.8f, 0.0f, 0.0f));
    airplaneTransformation->addTransformation(std::make_shared<Rotation>(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    airplaneTransformation->addTransformation(std::make_shared<Rotation>(glm::radians(125.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    airplaneTransformation->addTransformation(airplaneSelfRotation);
    airplaneTransformation->addTransformation(std::make_shared<Scale>(0.4f, 0.4f, 0.4f));
    airplane->setTransformation(airplaneTransformation);
    scene5->addObject(airplane);
}

void Application::createClockScene()
{
    auto object = std::make_shared<DrawableObject>(clock, clockShader);
    object->setTransformation(std::make_shared<Scale>(-1.0f, 1.0f, 1.0f));
    scene6->addObject(object);
}

void Application::createLightingScene()
{
    glm::vec3 positions[] = {
        glm::vec3(-1.1f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.1f, 0.0f),
        glm::vec3(1.1f, 0.0f, 0.0f),
        glm::vec3(0.0f, -1.1f, 0.0f)
    };
    ShaderProgram* shaders[] = { ambientShader, lambertShader, phongShader, blinnShader };

    for (int i = 0; i < 4; i++)
    {
        auto sphere = std::make_shared<DrawableObject>(sphereModel, shaders[i]);
        auto transformation = std::make_shared<CompositeTransformation>();
        transformation->addTransformation(std::make_shared<Translation>(positions[i].x, positions[i].y, positions[i].z));
        transformation->addTransformation(std::make_shared<Scale>(0.5f, 0.5f, 0.5f));
        sphere->setTransformation(transformation);
        sphere->setColor(glm::vec3(0.385f, 0.647f, 0.812f));
        scene7->addObject(sphere);
    }
}
