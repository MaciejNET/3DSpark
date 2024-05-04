#include "../include/Engine.h"
#include "../include/Entities/RectangularEntity.h"
#include "../include/Entities/SphereEntity.h"
#include "../include/Entities/CylinderEntity.h"
#include "../include/Entities/ConeEntity.h"

int main()
{
    Engine engine(800, 600, "3DSpark");

    RectangularEntity rectangularEntity;
    rectangularEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    rectangularEntity.SetTexture(new ImageTexture("../assets/image2.jpeg"));

    SphereEntity sphereEntity;
    sphereEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    sphereEntity.SetTexture(new ImageTexture("../assets/image2.jpeg"));

    CylinderEntity cylinderEntity;
    cylinderEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    cylinderEntity.SetTexture(new ImageTexture("../assets/image2.jpeg"));

    ConeEntity coneEntity;
    coneEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    coneEntity.SetTexture(new ImageTexture("../assets/image2.jpeg"));

    //engine.AddEntityToRenderer(&rectangularEntity);
    //engine.AddEntityToRenderer(&sphereEntity);
    //engine.AddEntityToRenderer(&cylinderEntity);
    engine.AddEntityToRenderer(&coneEntity);

    engine.Run();
    return 0;
}