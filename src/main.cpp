#include "../include/Engine.h"
#include "../include/Entities/RectangularEntity.h"
#include "../include/Entities/SphereEntity.h"
#include "../include/Entities/CylinderEntity.h"
#include "../include/Entities/ConeEntity.h"
#include <string>

const std::string leaves = "leaves.jpeg";
const std::string goldOre = "gold_ore.jpeg";

#ifdef __unix__
    const std::string leavesTexturePath = "../assets/" + leaves;
    const std::string goldOreTexturePath = "../assets/" + goldOre;
#elif __aarch64__ || __APPLE__
    const std::string leavesTexturePath = "../assets/" + leaves;
    const std::string goldOreTexturePath = "../assets/" + goldOre;
#elif defined(_WIN32) || defined(_WIN64)
    const std::string leavesTexturePath = "../../../assets/" + leaves;
    const std::string goldOreTexturePath = "../../../assets/" + goldOre;
#endif

int main()
{
    Engine engine(1280, 960, "3DSpark");
    engine.TurnOffCursor();

    RectangularEntity rectangularEntity;
    rectangularEntity.SetTexture(new ImageTexture(goldOreTexturePath));
    rectangularEntity.Translate(glm::vec3(2.5f, 0.0f, 0.0f));

    SphereEntity sphereEntity;
    sphereEntity.SetTexture(new ImageTexture(leavesTexturePath));
    sphereEntity.Translate(glm::vec3(-2.5f, 0.0f, 0.0f));

    CylinderEntity cylinderEntity;
    cylinderEntity.SetTexture(new GradientTexture(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
    cylinderEntity.Translate(glm::vec3(0.0f, 0.0f, 2.5f));

    ConeEntity coneEntity;
    coneEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));

    RectangularEntity bottom;
    bottom.SetTexture(new ColorTexture(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)));
    bottom.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
    bottom.Scale(glm::vec3(15.0f, 0.1f, 15.0f));

    engine.AddEntityToRenderer(&rectangularEntity);
    engine.AddEntityToRenderer(&sphereEntity);
    engine.AddEntityToRenderer(&cylinderEntity);
    engine.AddEntityToRenderer(&coneEntity);
    engine.AddEntityToRenderer(&bottom);

    engine.Run();
    return 0;
}