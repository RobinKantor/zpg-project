/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

#include <glm/glm.hpp>
#include <vector>

class CameraObserver;

class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	float alpha;
	float fi;
	float aspectRatio;
	std::vector<CameraObserver*> observers;

	void updateView();
	void updateProjection();
	void notify();

public:
	Camera();
	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	void setPose(const glm::vec3& eye, float alpha, float fi);
	void move(float forward, float right);
	void rotate(float deltaX, float deltaY);
	void resize(int width, int height);
	void attach(CameraObserver* observer);
	void detach(CameraObserver* observer);
};
