#ifndef INC_3DSPARK_SPHEREENTITY_H
#define INC_3DSPARK_SPHEREENTITY_H

#include "Entity.h"

class SphereEntity : public Entity
{
public:
    SphereEntity() = default;
    ~SphereEntity() override = default;
    void Draw() override;
    void Update(float deltaTime) override;
};

#endif //INC_3DSPARK_SPHEREENTITY_H
