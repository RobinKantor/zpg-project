#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

#include "Application.h"

#include "Models/sphere.h"
#include "Models/KAN0310.h"


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

	float treePoints[] = {
		// Trunk
		-0.12f, -0.55f, 0.0f,   0.45f, 0.25f, 0.10f,
		 0.12f, -0.55f, 0.0f,   0.45f, 0.25f, 0.10f,
		 0.12f, -0.10f, 0.0f,   0.45f, 0.25f, 0.10f,

		-0.12f, -0.55f, 0.0f,   0.45f, 0.25f, 0.10f,
		 0.12f, -0.10f, 0.0f,   0.45f, 0.25f, 0.10f,
		-0.12f, -0.10f, 0.0f,   0.45f, 0.25f, 0.10f,

		// Crown
		-0.50f, -0.10f, 0.0f,   0.10f, 0.65f, 0.15f,
		 0.00f,  0.65f, 0.0f,   0.10f, 0.65f, 0.15f,
		 0.50f, -0.10f, 0.0f,   0.10f, 0.65f, 0.15f
	};


	float bushPoints[] = {
		-0.60f, -0.20f, 0.0f,   0.15f, 0.70f, 0.20f,
		-0.30f,  0.30f, 0.0f,   0.15f, 0.70f, 0.20f,
		 0.00f, -0.20f, 0.0f,   0.15f, 0.70f, 0.20f,

		-0.30f, -0.20f, 0.0f,   0.10f, 0.60f, 0.15f,
		 0.00f,  0.40f, 0.0f,   0.10f, 0.60f, 0.15f,
		 0.30f, -0.20f, 0.0f,   0.10f, 0.60f, 0.15f,

		 0.00f, -0.20f, 0.0f,   0.15f, 0.70f, 0.20f,
		 0.30f,  0.30f, 0.0f,   0.15f, 0.70f, 0.20f,
		 0.60f, -0.20f, 0.0f,   0.15f, 0.70f, 0.20f
	};

	model1 = new Model(points1, sizeof(points1), 3);
	model2 = new Model(points2, sizeof(points2), 3);

	sphereModel = new Model(sphere, sizeof(sphere), 2880);

	treeModel = new Model(treePoints, sizeof(treePoints), 9);
	bushModel = new Model(bushPoints, sizeof(bushPoints), 9);

	loginModel = new Model(
		loginKAN0310,
		sizeof(loginKAN0310),
		KAN0310_VERTEX_COUNT
	);
}

void Application::createScenes()
{
	scene1 = new Scene();
	scene2 = new Scene();
	scene3 = new Scene();
	scene4 = new Scene();

	scene1->addObject(
		model1,
		shader1
	);

	scene2->addObject(
		sphereModel,
		shader1,
		0.0f,
		0.0f,
		0.0f,
		0.7f
	);

	// Scene 3 - forest

	float treePositions[][2] = {
		{-0.85f,  0.45f},
		{-0.55f,  0.50f},
		{-0.25f,  0.42f},
		{ 0.05f,  0.50f},
		{ 0.35f,  0.43f},
		{ 0.62f,  0.48f},

		{-0.75f,  0.05f},
		{-0.45f,  0.10f},
		{-0.15f,  0.03f},
		{ 0.15f,  0.10f},
		{ 0.48f,  0.03f}
	};

	for (int i = 0; i < 11; i++)
	{
		scene3->addObject(
			treeModel,
			shader1,
			treePositions[i][0],
			treePositions[i][1],
			0.0f,
			0.25f
		);
	}

	float bushPositions[][2] = {
	{-0.88f, -0.42f},
	{-0.68f, -0.30f},
	{-0.48f, -0.43f},
	{-0.28f, -0.32f},
	{-0.08f, -0.45f},
	{ 0.12f, -0.30f},
	{ 0.32f, -0.43f},
	{ 0.52f, -0.31f},
	{ 0.72f, -0.43f},
	{ 0.86f, -0.25f},
	{ 0.00f, -0.12f}
	};

	for (int i = 0; i < 11; i++)
	{
		scene3->addObject(
			bushModel,
			shader1,
			bushPositions[i][0],
			bushPositions[i][1],
			0.0f,
			0.18f
		);
	}

	scene3->addObject(
		sphereModel,
		shader2,
		0.75f,
		0.75f,
		0.0f,
		0.15f
	);

	// Scene 4 - login
	scene4->addObject(
		loginModel,
		shader2,
		0.0f,
		0.0f,
		0.0f,
		0.8f
	);

	// Login signature in scene 1
	scene1->addObject(
		loginModel,
		shader2,
		0.72f,
		-0.82f,
		-0.1f,
		0.20f
	);

	// Login signature in scene 2
	scene2->addObject(
		loginModel,
		shader2,
		0.72f,
		-0.82f,
		-0.1f,
		0.20f
	);

	// Login signature in scene 3
	scene3->addObject(
		loginModel,
		shader2,
		0.72f,
		-0.82f,
		-0.1f,
		0.20f
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


		// Translation
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			moveX -= 0.01f;

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			moveX += 0.01f;

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			moveY += 0.01f;

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			moveY -= 0.01f;

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


		// Rotation around X
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			rotationX += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			rotationX -= 0.02f;


		// Rotation around Y
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			rotationY += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			rotationY -= 0.02f;


		// Rotation around Z
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			rotationZ += 0.02f;

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			rotationZ -= 0.02f;


		// Reset transformations
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


		// Update login model in scene 4
		scene4->setObjectTransform(
			0,
			moveX,
			moveY,
			moveZ,
			objectScale,
			rotationX,
			rotationY,
			rotationZ
		);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		activeScene->draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}