#ifndef INC_2DSPARK_INPUTMANAGER_H
#define INC_2DSPARK_INPUTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Events/KeyHeldEvent.h"
#include <memory>

class InputManager
{
public:
    static void Initialize();
    static void Update();
    static bool KeyPressed(int key);
    static bool KeyReleased(int key);
    static bool MouseButtonPressed(int button);
    static bool MouseButtonReleased(int button);
    static double GetMouseX();
    static double GetMouseY();
    static bool KeyHeld(int key);

private:
    static bool _keys[512];
    static bool _prevKeys[512];
    static bool _mouseButtons[8];
    static bool _prevMouseButtons[8];
    static double _mouseX, _mouseY;
    static double _keyPressTime[512];
    static bool _isKeyHeld;
};

#endif // INC_2DSPARK_INPUTMANAGER_H