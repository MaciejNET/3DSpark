#include "../include/Renderer.h"

void Renderer::Render(float deltaTime)
{
    _camera.Update();
    for (auto& entity : _entities)
    {
        entity->SetCameraMatrices(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());
        entity->Draw();
        entity->Update(deltaTime);
    }
}

void Renderer::AddEntity(Entity* entity)
{
    _entities.push_back(entity);
}

void Renderer::RemoveEntity(Entity* entity)
{
    _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void Renderer::ClearEntities()
{
    _entities.clear();
}