#ifndef INC_3DSPARK_RENDERER_H
#define INC_3DSPARK_RENDERER_H

#include "Entities/Entity.h"
#include <vector>

class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    void Render(float deltaTime);
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    void ClearEntities();

private:
    std::vector<Entity*> _entities;
};

#endif //INC_3DSPARK_RENDERER_H
