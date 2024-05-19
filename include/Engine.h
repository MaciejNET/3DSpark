#ifndef INC_3DSPARK_ENGINE_H
#define INC_3DSPARK_ENGINE_H

#include "Entities/Entity.h"
#include "Renderer.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);
    Engine(int width, int height, const char* title, float targetFps);
    ~Engine();

    void Run();
    void AddEntityToRenderer(Entity* entity);
    void RemoveEntityFromRenderer(Entity* entity);
    void ClearEntitiesFromRenderer();
    void SetTargetFps(float targetFps);
    void TurnOnCursor();
    void TurnOffCursor();

private:
    float _targetFps{};
    Renderer* _renderer;
    float _deltaTime{};
    float _lastFrame{};
    float _fps{};
};

#endif //INC_3DSPARK_ENGINE_H
