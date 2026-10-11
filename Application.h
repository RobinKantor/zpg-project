#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Model.h"
#include "Scene.h"

class Application {

private:
	GLFWwindow* window;
	ShaderProgram* shader1;
	ShaderProgram* shader2;
	Model* model1;
	Model* model2;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float moveZ = 0.0f;

	float objectScale = 0.8f;

	float rotationX = 0.0f;
	float rotationY = 0.0f;
	float rotationZ = 0.0f;
	Scene* scene1;
	Scene* scene2;
	Scene* scene3;
	Scene* scene4;

	Scene* activeScene;
	Model* sphereModel;
	Model* treeModel;
	Model* bushModel;
	Model* loginModel;

public:
	void initialization();
	void createShaders();
	void createModels();
	void createScenes();
	void run();
};