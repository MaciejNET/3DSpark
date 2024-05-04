#include "../include/Engine.h"
#include "../include/Managers/WindowManager.h"
#include "../include/Managers/InputManager.h"
#include "Events/EventBus.h"
#include <iostream>
#include <thread>

Engine::Engine(int width, int height, const char* title)
{
    WindowManager::Initialize(width, height, title);
    InputManager::Initialize();
    _renderer = new Renderer();
}

Engine::Engine(int width, int height, const char* title, float targetFps) : Engine(width, height, title)
{
    SetTargetFps(targetFps);
}

Engine::~Engine()
{
    WindowManager::Cleanup();
}

void Engine::Run()
{
    while (!glfwWindowShouldClose(WindowManager::GetWindow()))
    {
        auto startFrame = static_cast<float>(glfwGetTime());

        InputManager::Update();

        if (InputManager::KeyPressed(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(WindowManager::GetWindow(), true);
        }

        if (InputManager::KeyPressed(GLFW_KEY_F10))
        {
            WindowManager::ToggleFullscreen();
        }

        if (InputManager::KeyPressed(GLFW_KEY_F9))
        {
            WindowManager::ToggleWindowed();
        }

        WindowManager::ClearScreen();
        _renderer->Render(_deltaTime);
        EventBus::DispatchEvents();

        glfwSwapBuffers(WindowManager::GetWindow());
        glfwPollEvents();

        auto endFrame = static_cast<float>(glfwGetTime());
        _deltaTime = endFrame - startFrame;

        if (_targetFps > 0)
        {
            auto targetFrameTime = 1.0f / _targetFps;
            auto sleepTime = targetFrameTime - _deltaTime;
            if (sleepTime > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepTime * 1000)));
                _deltaTime = targetFrameTime;
            }
        }

        _fps = 1.0f / _deltaTime;
        std::cout << "FPS: " << _fps << std::endl;
    }
}

void Engine::SetTargetFps(float targetFps)
{
    _targetFps = targetFps;
}

void Engine::AddEntityToRenderer(Entity* entity)
{
    _renderer->AddEntity(entity);
}

void Engine::RemoveEntityFromRenderer(Entity* entity)
{
    _renderer->RemoveEntity(entity);
}

void Engine::ClearEntitiesFromRenderer()
{
    _renderer->ClearEntities();
}
