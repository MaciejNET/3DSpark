#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <memory>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Resolution
{
    int width;
    int height;
};

/**
 * @brief Klasa WindowManager odpowiada za zarządzanie oknem aplikacji.
 */
class WindowManager
{
public:
    /**
     * @brief Metoda Initialize inicjalizuje WindowManager.
     * @param width szerokość okna
     * @param height wysokość okna
     * @param title tytuł okna
     */
    static void Initialize(int width = 1024, int height = 768, const char* title = "Window");

    /**
     * @brief Metoda Cleanup czyści zasoby WindowManagera.
     */
    static void Cleanup();

    /**
     * @brief Metoda GetWindow zwraca wskaźnik na okno.
     * @return wskaźnik na okno
     */
    static GLFWwindow* GetWindow();

    /**
     * @brief Metoda zwraca szerokość okna.
     * @return szerokość okna
     */
    static int GetWidth();

    /**
     * @brief Metoda zwraca wysokość okna.
     * @return wysokość okna
     */
    static int GetHeight();

    /**
     * @brief Metoda SetResolution ustawia rozdzielczość okna.
     * @param width szerokość okna
     * @param height wysokość okna
     */
    static void SetResolution(int width, int height);

    /**
     * @brief Metoda SetTitle ustawia tytuł okna.
     * @param title tytuł okna
     */
    static void SetTitle(const char* title);

    /**
     * @brief Metoda ToggleFullscreen przełącza okno w tryb pełnoekranowy.
     */
    static void ToggleFullscreen();

    /**
     * @brief Metoda ToggleWindowed przełącza okno w tryb okienkowy.
     */
    static void ToggleWindowed();

    /**
     * @brief Metoda ClearScreen czyści ekran.
     */
    static void ClearScreen();

    /**
     * @brief Metoda ustawia kolor czyszczenia ekranu.
     */
    static void SetClearColor(float r, float g, float b, float a);

    /**
     * @brief Metoda włącza kursor myszy.
     */
    static void TurnOnCursor();

    /**
     * @brief Metoda wyłącza kursor myszy.
     */
    static void TurnOffCursor();

private:
    /**
     * @brief Metoda FramebufferSizeCallback obsługuje zmianę rozmiaru okna.
     * @param window wskaźnik na okno
     * @param width szerokość okna
     * @param height wysokość okna
     */
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    /**
     * @brief Metoda UpdateViewport aktualizuje widok.
     * @param width szerokość okna
     * @param height wysokość okna
     */
    static void UpdateViewport(int width, int height);

    static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
    static std::vector<Resolution> resolutions;
    static int currentResolutionIndex;
    static bool _isFullscreen;
    static float _clearColor[4];
};

#endif
