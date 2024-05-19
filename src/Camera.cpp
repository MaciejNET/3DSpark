#include "../include/Camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "../include/Managers/InputManager.h"
#include "Managers/WindowManager.h"

Camera::Camera(int width, int height)
    : _width(width), _height(height)
{
}

void Camera::Update()
{
    SetWidth(WindowManager::GetWidth());
    SetHeight(WindowManager::GetHeight());

    if (InputManager::KeyHeld(GLFW_KEY_W))
    {
        _position += _speed * _orientation;
    }
    if (InputManager::KeyHeld(GLFW_KEY_S))
    {
        _position -= _speed * _orientation;
    }
    if (InputManager::KeyHeld(GLFW_KEY_A))
    {
        glm::vec3 right = glm::normalize(glm::cross(_orientation, _up));
        _position -= _speed * right;
    }
    if (InputManager::KeyHeld(GLFW_KEY_D))
    {
        glm::vec3 right = glm::normalize(glm::cross(_orientation, _up));
        _position += _speed * right;
    }
    if (InputManager::KeyHeld(GLFW_KEY_SPACE))
    {
        _position += _speed * _up;
    }
    if (InputManager::KeyHeld(GLFW_KEY_LEFT_SHIFT))
    {
        _position -= _speed * _up;
    }

    double xpos = InputManager::GetMouseX();
    double ypos = InputManager::GetMouseY();

    static double lastX = xpos;
    static double lastY = ypos;

    auto xoffset = (float)(lastX - xpos);
    auto yoffset = (float)(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    Rotate(xoffset, yoffset);
}

void Camera::Rotate(float x, float y)
{
    _orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), glm::radians(x / _sensitivity), _up) * glm::vec4(_orientation, 0.0f));
    glm::vec3 right = glm::normalize(glm::cross(_orientation, _up));
    _orientation = glm::normalize(glm::rotate(glm::mat4(1.0f), glm::radians(y / _sensitivity), right) * glm::vec4(_orientation, 0.0f));
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(_position, _position + _orientation, _up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
}

void Camera::SetPosition(glm::vec3 position)
{
    _position = position;
}

void Camera::SetOrientation(glm::vec3 orientation)
{
    _orientation = orientation;
}

void Camera::SetUp(glm::vec3 up)
{
    _up = up;
}

void Camera::SetSpeed(float speed)
{
    _speed = speed;
}

void Camera::SetSensitivity(float sensitivity)
{
    _sensitivity = sensitivity;
}

void Camera::SetWidth(int width)
{
    _width = width;
}

void Camera::SetHeight(int height)
{
    _height = height;
}
