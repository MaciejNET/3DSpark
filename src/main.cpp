#include "../include/Engine.h"
#include "../include/Entities/RectangularEntity.h"
#include "../include/Entities/SphereEntity.h"
#include "../include/Entities/CylinderEntity.h"
#include "../include/Entities/ConeEntity.h"
#include <string>

const std::string imageName = "image2.jpeg";

#ifdef __unix__
    const std::string imageTexturePath = "../assets/" + imageName;
#elif __aarch64__ || __APPLE__
    const std::string imageTexturePath = "../assets/" + imageName;
#elif defined(_WIN32) || defined(_WIN64)
    const std::string imageTexturePath = "../../../assets/" + imageName;
#endif

int main()
{
    Engine engine(800, 600, "3DSpark");
    engine.TurnOffCursor();

    RectangularEntity rectangularEntity;
    rectangularEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    rectangularEntity.SetTexture(new ImageTexture(imageTexturePath));

    SphereEntity sphereEntity;
    sphereEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    sphereEntity.SetTexture(new ImageTexture(imageTexturePath));

    CylinderEntity cylinderEntity;
    cylinderEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    cylinderEntity.SetTexture(new ImageTexture(imageTexturePath));

    ConeEntity coneEntity;
    coneEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    coneEntity.SetTexture(new ImageTexture(imageTexturePath));

    //engine.AddEntityToRenderer(&rectangularEntity);
    //engine.AddEntityToRenderer(&sphereEntity);
    //engine.AddEntityToRenderer(&cylinderEntity);
    engine.AddEntityToRenderer(&coneEntity);

    engine.Run();
    return 0;
}