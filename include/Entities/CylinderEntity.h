#ifndef INC_3DSPARK_CYLINDERENTITY_H
#define INC_3DSPARK_CYLINDERENTITY_H

#include "Entity.h"

class CylinderEntity : public Entity
{
public:
    CylinderEntity() = default;
    ~CylinderEntity() override = default;
    void Draw() override;
    void Update(float deltaTime) override;
};

#endif //INC_3DSPARK_CYLINDERENTITY_H
