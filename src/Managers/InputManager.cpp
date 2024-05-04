#include "../../include/Managers/InputManager.h"
#include "../../include/Events/EventBus.h"
#include "../../include/Events/KeyPressedEvent.h"
#include "../../include/Events/MouseMovedEvent.h"
#include "GLFW/glfw3.h"
#include "../../include/Events/KeyReleasedEvent.h"
#include "../../include/Managers/WindowManager.h"

bool InputManager::_keys[512];
bool InputManager::_prevKeys[512];
bool InputManager::_mouseButtons[8];
bool InputManager::_prevMouseButtons[8];
double InputManager::_mouseX;
double InputManager::_mouseY;
double InputManager::_keyPressTime[512];
bool InputManager::_isKeyHeld;

void InputManager::Initialize()
{
    for (int i = 0; i < 512; i++)
    {
        _keys[i] = false;
        _prevKeys[i] = false;
        _keyPressTime[i] = 0.0;
    }
    for (int i = 0; i < 8; i++)
    {
        _mouseButtons[i] = false;
        _prevMouseButtons[i] = false;
    }
    _mouseX = 0.0;
    _mouseY = 0.0;
}

bool InputManager::KeyPressed(int key)
{
    return _keys[key] && !_prevKeys[key];
}

bool InputManager::KeyReleased(int key)
{
    return !_keys[key] && _prevKeys[key];
}

bool InputManager::MouseButtonPressed(int button)
{
    return _mouseButtons[button] && !_prevMouseButtons[button];
}

bool InputManager::MouseButtonReleased(int button)
{
    return !_mouseButtons[button] && _prevMouseButtons[button];
}

double InputManager::GetMouseX()
{
    return _mouseX;
}

double InputManager::GetMouseY()
{
    return _mouseY;
}

bool InputManager::KeyHeld(int key)
{
    return _keys[key] && _prevKeys[key];
}

void InputManager::Update()
{
    auto window = WindowManager::GetWindow();
    for (int i = 0; i < 512; i++)
    {
        _prevKeys[i] = _keys[i];
        _keys[i] = glfwGetKey(window, i);

        if (_keys[i] && !_prevKeys[i])
        {
            _keyPressTime[i] = glfwGetTime();
        }

        if (KeyPressed(i))
        {
            std::shared_ptr<Event> event = std::make_shared<KeyPressedEvent>(i);
            EventBus::Publish(event);
        }
        else if (KeyHeld(i))
        {
            if (glfwGetTime() - _keyPressTime[i] > 0.1)
            {
                _isKeyHeld = true;
                std::shared_ptr<Event> event = std::make_shared<KeyHeldEvent>(i);
                EventBus::Publish(event);
            }
        }

        if (KeyReleased(i) && _isKeyHeld)
        {
            _isKeyHeld = false;
            std::shared_ptr<Event> event = std::make_shared<KeyReleasedEvent>(i);
            EventBus::Publish(event);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        _prevMouseButtons[i] = _mouseButtons[i];
        _mouseButtons[i] = glfwGetMouseButton(window, i);
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    _mouseX = x;
    _mouseY = y;

    std::shared_ptr<Event> event = std::make_shared<MouseMovedEvent>(_mouseX, _mouseY);
    EventBus::Publish(event);
}
