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

    std::function<void(Entity&, float)> rotateEntityAroundY = [](Entity& entity, float deltaTime) {
        float rotationSpeed = 10.0f;
        entity.Rotate(glm::vec3(0.0f, 0.1f, 0.0f), rotationSpeed * deltaTime);
    };

    std::function<void(Entity&, float)> rotateEntityAroundZ = [](Entity& entity, float deltaTime) {
        float rotationSpeed = 10.0f;
        entity.Rotate(glm::vec3(0.0f, 0.0f, 0.1f), rotationSpeed * deltaTime);
    };

    std::function<void(Entity&, float)> rotateEntityAroundYAndScale = [scaleUp = true](Entity& entity, float deltaTime) mutable {
        float rotationSpeed = 10.0f;
        float scaleSpeed = 0.005f;
        glm::vec3 currentScale = entity.GetScale();

        if (scaleUp)
        {
            if (currentScale.x < 1.5f)
            {
                entity.Scale(glm::vec3(1.0f + scaleSpeed, 1.0f + scaleSpeed, 1.0f + scaleSpeed));
            }
            else
            {
                scaleUp = false;
            }
        }
        else
        {
            if (currentScale.x > 0.5f)
            {
                entity.Scale(glm::vec3(1.0f - scaleSpeed, 1.0f - scaleSpeed, 1.0f - scaleSpeed));
            }
            else
            {
                scaleUp = true;
            }
        }

        entity.Rotate(glm::vec3(0.0f, 0.1f, 0.0f), rotationSpeed * deltaTime);
    };

    RectangularEntity rectangularEntity;
    rectangularEntity.SetTexture(new ImageTexture(goldOreTexturePath));
    rectangularEntity.Translate(glm::vec3(2.5f, 0.0f, 0.0f));
    rectangularEntity.SetUpdateFunction(rotateEntityAroundY);

    SphereEntity sphereEntity;
    sphereEntity.SetTexture(new ImageTexture(leavesTexturePath));
    sphereEntity.Translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    sphereEntity.SetUpdateFunction(rotateEntityAroundYAndScale);

    CylinderEntity cylinderEntity;
    cylinderEntity.SetTexture(new GradientTexture(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
    cylinderEntity.Translate(glm::vec3(0.0f, 0.0f, 2.5f));
    cylinderEntity.SetUpdateFunction(rotateEntityAroundZ);

    ConeEntity coneEntity;
    coneEntity.SetTexture(new ColorTexture(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    coneEntity.SetUpdateFunction(rotateEntityAroundZ);

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