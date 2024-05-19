#ifndef INC_3DSPARK_RENDERER_H
#define INC_3DSPARK_RENDERER_H

#include "Entities/Entity.h"
#include "Managers/WindowManager.h"
#include "Camera.h"
#include <vector>

class Renderer
{
public:
    Renderer() : _camera(Camera(WindowManager::GetWidth(), WindowManager::GetHeight())) {}
    ~Renderer() = default;

    void Render(float deltaTime);
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void ClearEntities();

private:
    std::vector<Entity*> _entities;
    Camera _camera;
};

#endif //INC_3DSPARK_RENDERER_H
