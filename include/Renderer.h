#ifndef INC_3DSPARK_RENDERER_H
#define INC_3DSPARK_RENDERER_H

#include "Entities/Entity.h"
#include "Managers/WindowManager.h"
#include "Camera.h"
#include "LightPoint.h"
#include <vector>

class Renderer
{
public:
    Renderer() : _camera(new Camera(WindowManager::GetWidth(), WindowManager::GetHeight())),
        _lightPoint(new LightPoint())
    {
    }

    ~Renderer() = default;

    void Render(float deltaTime, bool isLightingEnabled, bool isShadingEnabled);
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void ClearEntities();

    Camera* GetCamera() const { return _camera; };
    LightPoint* GetLightPoint() const { return _lightPoint; };

private:
    std::vector<Entity*> _entities;
    Camera* _camera;
    LightPoint* _lightPoint;
};

#endif //INC_3DSPARK_RENDERER_H
