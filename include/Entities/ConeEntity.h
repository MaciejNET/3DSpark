#ifndef INC_3DSPARK_CONEENTITY_H
#define INC_3DSPARK_CONEENTITY_H

#include "Entity.h"

class ConeEntity : public Entity
{
public:
    ConeEntity() = default;
    ~ConeEntity() override = default;
    void Draw() override;
    void Update(float deltaTime) override;
};

#endif //INC_3DSPARK_CONEENTITY_H
