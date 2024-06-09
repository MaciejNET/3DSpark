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
    Renderer() : _camera(Camera(WindowManager::GetWidth(), WindowManager::GetHeight())), _lightPoint()
    {
        _lightPoint.Translate(glm::vec3(7.0f, 7.0f, 7.0f));
        _lightPoint.Scale(glm::vec3(2.0f, 2.0f, 2.0f));
    }

    ~Renderer() = default;

    void Render(float deltaTime, bool isLightingEnabled, bool isShadingEnabled);
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void ClearEntities();

private:
    std::vector<Entity*> _entities;
    Camera _camera;
    LightPoint _lightPoint;
};

#endif //INC_3DSPARK_RENDERER_H
