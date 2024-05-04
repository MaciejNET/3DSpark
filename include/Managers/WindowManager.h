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

class WindowManager
{
public:
    static void Initialize(int width = 1024, int height = 768, const char* title = "Window");
    static void Cleanup();
    static GLFWwindow* GetWindow();
    static void SetResolution(int width, int height);
    static void SetTitle(const char* title);
    static void ToggleFullscreen();
    static void ToggleWindowed();
    static void ClearScreen();
    static void SetClearColor(float r, float g, float b, float a);

private:
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void UpdateViewport(int width, int height);

    static std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> _window;
    static std::vector<Resolution> resolutions;
    static int currentResolutionIndex;
    static bool _isFullscreen;
    static float _clearColor[4];
};

#endif
