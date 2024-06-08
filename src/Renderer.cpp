#include "../include/Renderer.h"

void Renderer::Render(float deltaTime)
{
    _camera.Update();
    _lightPoint.SetCameraMatrices(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());
    _lightPoint.Draw();
    _lightPoint.Update(deltaTime);
    for (auto& entity : _entities)
    {
        entity->SetCameraMatrices(_camera.GetViewMatrix(), _camera.GetProjectionMatrix());
        entity->SetCameraPosition(_camera.GetPosition());
        entity->SetLightColor(_lightPoint.GetColor());
        entity->SetLightPosition(_lightPoint.GetPosition());
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