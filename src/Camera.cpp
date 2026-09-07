#include "Camera.hpp"

Camera::Camera(World* _world, Vec3 _pos, Vec3 _forward, Vec3 _up, Vec3 _right, float _fov)
{
    world = _world;
    pos = _pos;
    forward = _forward;
    up = _up;
    right = _right;

    fov = _fov;

    culling = true;
    lock = true;
}

World* Camera::getWorld()
{
    return world;
}

void Camera::setWorld(World* _world)
{
    world = _world;
}

Vec3 Camera::getPos()
{
    return pos;
}

void Camera::setPos(int index, float value)
{
    pos.set(index, value);
}

void Camera::moveTowards(Vec3 point, float distance)
{
    Vec3 direction = point.subtract(pos);
    direction.normalize();

    pos = pos.add(direction.multiply(distance));

    if(!lock)
    {
        forward = forward.add(direction.multiply(distance));
        forward.normalize();
    }
}

Vec3 Camera::getForward()
{
    return forward;
}

void Camera::setForward(int index, float value)
{
    forward.set(index, value);
}

Vec3 Camera::getUp()
{
    return up;
}

void Camera::setUp(int index, float value)
{
    up.set(index, value);
}

Vec3 Camera::getRight()
{
    return right;
}

void Camera::setRight(int index, float value)
{
    right.set(index, value);
}

float Camera::getFov()
{
    return fov;
}

void Camera::setFov(float _fov)
{
    fov = _fov;
}

bool Camera::getCulling()
{
    return culling;
}

void Camera::setCulling(bool _culling)
{
    culling = _culling;
}

bool Camera::getLock()
{
    return lock;
}

void Camera::setLock(bool _lock)
{
    lock = _lock;
    if(!_lock)
    {
        normalizeForward();
    }
}

void Camera::normalizeForward()
{
    forward = forward.normalize();
}

void Camera::normalizeUp()
{
    up = up.normalize();
}

void Camera::normalizeRight()
{
    right = right.normalize();
}

void Camera::updateRight()
{
    right = forward.cross(up);
}

Vec3 Camera::project(float scale, Vec3 point)
{
    float x = (point.get(0) * scale) / point.get(2);
    float y = (point.get(1) * scale) / point.get(2);

    return Vec3(x, y, point.get(2), point.getColour());
}