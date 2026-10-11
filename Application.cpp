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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <random>


void Application::initialization() {

	// Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Initialization of a specific version
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/


	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		exit(EXIT_FAILURE);
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::createShaders() {
	shader1 = new ShaderProgram(
		"shaders/basic.vert",
		"shaders/basic.frag"
	);

	shader2 = new ShaderProgram(
		"shaders/basic.vert",
		"shaders/basic2.frag"
	);
}

void Application::createModels()
{
	float points1[] = {
		-0.7f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		-0.3f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.9f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	float points2[] = {
		 0.7f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.9f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.3f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	model1 = new Model(points1, sizeof(points1), 3);
	model2 = new Model(points2, sizeof(points2), 3);

	sphereModel = new Model(sphere, sizeof(sphere), 2880);

    treeModel = new Model(
        tree,
        sizeof(tree),
        sizeof(tree) / (6 * sizeof(float))
    );

    bushModel = new Model(
        bushes,
        sizeof(bushes),
        sizeof(bushes) / (6 * sizeof(float))
    );

	loginModel = new Model(
		loginKAN0310,
		sizeof(loginKAN0310),
		KAN0310_VERTEX_COUNT
	);

    sunModel = new Model(
        sun,
        sizeof(sun),
        11520,
        9
    );

    earthModel = new Model(
        earth,
        sizeof(earth),
        11520,
        9
    );

    moonModel = new Model(
        moon,
        sizeof(moon),
        11520,
        9
    );
}

void Application::createScenes()
{
    scene1 = new Scene();
    scene2 = new Scene();
    scene3 = new Scene();
    scene4 = new Scene();
    scene5 = new Scene();


    // ---------------------------------------------------------
    // Scene 1 - triangle
    // ---------------------------------------------------------

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


    // Login signature
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


    // ---------------------------------------------------------
    // Scene 2 - sphere
    // ---------------------------------------------------------

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

    sphereObject->setTransformation(
        sphereTransformation
    );

    scene2->addObject(
        sphereObject
    );


    // Login signature
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


    // ---------------------------------------------------------
    // Scene 3 - forest
    // ---------------------------------------------------------

    // trees
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<float> treeX(-0.85f, 0.55f);
    std::uniform_real_distribution<float> treeY(-0.05f, 0.50f);
    std::uniform_real_distribution<float> treeScale(0.06f, 0.085f);
    std::uniform_real_distribution<float> treeRotation(-0.4f, 0.4f);

    for (int i = 0; i < 15; i++)
    {
        auto treeObject =
            std::make_shared<DrawableObject>(
                treeModel,
                shader1
            );

        auto transformation =
            std::make_shared<CompositeTransformation>();

        transformation->addTransformation(
            std::make_shared<Translation>(
                treeX(generator),
                treeY(generator),
                0.0f
            )
        );

        transformation->addTransformation(
            std::make_shared<Rotation>(
                treeRotation(generator),
                glm::vec3(0.0f, 1.0f, 0.0f)
            )
        );

        float scale = treeScale(generator);

        transformation->addTransformation(
            std::make_shared<Scale>(
                scale,
                scale,
                scale
            )
        );

        treeObject->setTransformation(
            transformation
        );

        scene3->addObject(
            treeObject
        );
    }

    // bushes
    std::uniform_real_distribution<float> bushX(-0.90f, 0.90f);
    std::uniform_real_distribution<float> bushY(-0.65f, -0.15f);
    std::uniform_real_distribution<float> bushScale(0.40f, 0.65f);
    std::uniform_real_distribution<float> bushRotation(-0.5f, 0.5f);

    for (int i = 0; i < 15; i++)
    {
        auto bushObject =
            std::make_shared<DrawableObject>(
                bushModel,
                shader1
            );

        auto transformation =
            std::make_shared<CompositeTransformation>();

        transformation->addTransformation(
            std::make_shared<Translation>(
                bushX(generator),
                bushY(generator),
                0.0f
            )
        );

        transformation->addTransformation(
            std::make_shared<Rotation>(
                bushRotation(generator),
                glm::vec3(0.0f, 1.0f, 0.0f)
            )
        );

        float scale = bushScale(generator);

        transformation->addTransformation(
            std::make_shared<Scale>(
                scale,
                scale,
                scale
            )
        );

        bushObject->setTransformation(
            transformation
        );

        scene3->addObject(
            bushObject
        );
    }

    // Sun
    auto sun =
        std::make_shared<DrawableObject>(
            sphereModel,
            shader2
        );

    auto sunTransformation =
        std::make_shared<CompositeTransformation>();

    sunTransformation->addTransformation(
        std::make_shared<Translation>(
            0.75f,
            0.75f,
            0.0f
        )
    );

    sunTransformation->addTransformation(
        std::make_shared<Scale>(
            0.15f,
            0.15f,
            0.15f
        )
    );

    sun->setTransformation(
        sunTransformation
    );

    scene3->addObject(
        sun
    );


    // Login signature
    auto scene3Login =
        std::make_shared<DrawableObject>(
            loginModel,
            shader2
        );

    auto scene3LoginTransformation =
        std::make_shared<CompositeTransformation>();

    scene3LoginTransformation->addTransformation(
        std::make_shared<Translation>(
            0.72f,
            -0.82f,
            -0.1f
        )
    );

    scene3LoginTransformation->addTransformation(
        std::make_shared<Scale>(
            0.20f,
            0.20f,
            0.20f
        )
    );

    scene3Login->setTransformation(
        scene3LoginTransformation
    );

    scene3->addObject(
        scene3Login
    );


    // ---------------------------------------------------------
    // Scene 4 - controllable login
    // ---------------------------------------------------------

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

    // ---------------------------------------------------------
    // Scene 5 - Solar system
    // ---------------------------------------------------------

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


    activeScene = scene1;
}

void Application::run()
{
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        // Scene switching
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
            activeScene = scene1;

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            activeScene = scene2;

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
            activeScene = scene3;

        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
            activeScene = scene4;

        if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
            activeScene = scene5;


        // Translation X
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            moveX -= 0.01f;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            moveX += 0.01f;


        // Translation Y
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            moveY += 0.01f;

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            moveY -= 0.01f;


        // Translation Z
        if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
            moveZ += 0.01f;

        if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
            moveZ -= 0.01f;


        // Scale
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            objectScale += 0.01f;

        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            objectScale -= 0.01f;

            if (objectScale < 0.1f)
                objectScale = 0.1f;
        }


        // Rotation X
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            rotationX += 0.02f;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            rotationX -= 0.02f;


        // Rotation Y
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            rotationY += 0.02f;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            rotationY -= 0.02f;


        // Rotation Z
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            rotationZ += 0.02f;

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            rotationZ -= 0.02f;


        // Reset
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            moveX = 0.0f;
            moveY = 0.0f;
            moveZ = 0.0f;

            objectScale = 0.8f;

            rotationX = 0.0f;
            rotationY = 0.0f;
            rotationZ = 0.0f;
        }


        // Update transformations directly
        loginTranslation->setTranslation(
            moveX,
            moveY,
            moveZ
        );

        loginRotationX->setAngle(
            rotationX
        );

        loginRotationY->setAngle(
            rotationY
        );

        loginRotationZ->setAngle(
            rotationZ
        );

        loginScale->setScale(
            objectScale,
            objectScale,
            objectScale
        );

        // Solar system animation
        float time = static_cast<float>(glfwGetTime());

        sunRotation->setAngle(
            time * 0.3f
        );

        earthOrbitRotation->setAngle(
            time * 0.5f
        );

        earthSelfRotation->setAngle(
            time * 2.0f
        );

        moonOrbitRotation->setAngle(
            time * 2.0f
        );

        moonSelfRotation->setAngle(
            time * 1.5f
        );


        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        activeScene->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}