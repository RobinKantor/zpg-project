/**
 * @author Robin Kantor
 * @login KAN0310
 */

#pragma once

class Camera;

class CameraObserver
{
public:
    virtual void updateCamera(const Camera& camera) = 0;
    virtual ~CameraObserver() = default;
};
