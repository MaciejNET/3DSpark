#ifndef INC_2DSPARK_INPUTMANAGER_H
#define INC_2DSPARK_INPUTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Events/KeyHeldEvent.h"
#include <memory>

/**
 * @brief Klasa InputManager odpowiada za zarządzanie wejściem od użytkownika.
 */
class InputManager
{
public:
    /**
     * @brief Metoda Initialize inicjalizuje InputManager.
     */
    static void Initialize();

    /**
     * @brief Metoda Update aktualizuje stan InputManagera.
     */
    static void Update();

    /**
     * @brief Metoda KeyPressed zwraca true jeśli klawisz został wciśnięty.
     * @param key klawisz
     * @return true jeśli klawisz został wciśnięty
     */
    static bool KeyPressed(int key);

    /**
     * @brief Metoda KeyReleased zwraca true jeśli klawisz został zwolniony.
     * @param key klawisz
     * @return true jeśli klawisz został zwolniony
     */
    static bool KeyReleased(int key);

    /**
     * @brief Metoda MouseButtonPressed zwraca true jeśli przycisk myszy został wciśnięty.
     * @param button przycisk myszy
     * @return true jeśli przycisk myszy został wciśnięty
     */
    static bool MouseButtonPressed(int button);

    /**
     * @brief Metoda MouseButtonReleased zwraca true jeśli przycisk myszy został zwolniony.
     * @param button przycisk myszy
     * @return true jeśli przycisk myszy został zwolniony
     */
    static bool MouseButtonReleased(int button);

    /**
     * @brief Metoda GetMouseX zwraca pozycję myszy w osi X.
     * @return pozycja myszy w osi X
     */
    static double GetMouseX();

    /**
     * @brief Metoda GetMouseY zwraca pozycję myszy w osi Y.
     * @return pozycja myszy w osi Y
     */
    static double GetMouseY();

    /**
     * @brief Metoda KeyHeld zwraca true jeśli klawisz jest wciśnięty.
     * @param key klawisz
     * @return true jeśli klawisz jest wciśnięty
     */
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
