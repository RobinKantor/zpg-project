/**
 * @author Robin Kantor
 * @login KAN0310
 */

#include "Camera.h"
#include "CameraObserver.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <algorithm>
#include <cmath>

Camera::Camera()
    : eye(0.0f, 0.0f, 2.5f), up(0.0f, 1.0f, 0.0f),
      alpha(glm::half_pi<float>()), fi(-glm::half_pi<float>()),
      aspectRatio(4.0f / 3.0f)
{
    updateView();
    updateProjection();
}

const glm::mat4& Camera::getViewMatrix() const
{
    return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::setPose(const glm::vec3& eye, float alpha, float fi)
{
    this->eye = eye;
    this->alpha = glm::clamp(alpha, glm::radians(1.0f), glm::radians(179.0f));
    this->fi = std::remainder(fi, glm::two_pi<float>());
    updateView();
}

void Camera::move(float forward, float right)
{
    glm::vec3 direction = glm::normalize(target);
    glm::vec3 side = glm::normalize(glm::cross(direction, up));
    eye += direction * forward + side * right;
    updateView();
}

void Camera::rotate(float deltaX, float deltaY)
{
    alpha = glm::clamp(alpha + deltaY * 0.003f, glm::radians(1.0f), glm::radians(179.0f));
    fi = std::remainder(fi + deltaX * 0.003f, glm::two_pi<float>());
    updateView();
}

void Camera::resize(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    updateProjection();
}

void Camera::updateView()
{
    target.x = std::sin(alpha) * std::cos(fi);
    target.z = std::sin(alpha) * std::sin(fi);
    target.y = std::cos(alpha);
    viewMatrix = glm::lookAt(eye, eye + target, up);
    notify();
}

void Camera::updateProjection()
{
    projectionMatrix = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
    notify();
}

void Camera::attach(CameraObserver* observer)
{
    if (std::find(observers.begin(), observers.end(), observer) == observers.end())
        observers.push_back(observer);

    observer->updateCamera(*this);
}

void Camera::detach(CameraObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::notify()
{
    for (CameraObserver* observer : observers)
        observer->updateCamera(*this);
}
