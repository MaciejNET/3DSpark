#ifndef INC_3DSPARK_RECTANGULARENTITY_H
#define INC_3DSPARK_RECTANGULARENTITY_H

#include "Entity.h"

class RectangularEntity : public Entity
{
public:
    RectangularEntity() = default;
    ~RectangularEntity() override = default;
    void Draw() override;
    void Update(float deltaTime) override;
};

#endif //INC_3DSPARK_RECTANGULARENTITY_H
