#include "../include/Engine.h"
#include "../include/Entities/Entity.h"
#include "../include/Events/ObjectRotated180Event.h"
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

    std::function<void(Entity&, float)> rotateEntityAroundZAndPublishEvent = [totalRotation = 0.0f](Entity& entity, float deltaTime) mutable {
        float rotationSpeed = 7.5f;
        entity.Rotate(glm::vec3(0.0f, 0.0f, 0.1f), rotationSpeed * deltaTime);

        glm::vec3 currentRotation = entity.GetRotation();

        while (currentRotation.z >= 360.0f)
        {
            currentRotation.z -= 360.0f;
        }

        if (currentRotation.z >= 180.0f)
        {
            EventBus::Publish(std::make_shared<ObjectRotated180Event>());
        }
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

    std::function<void(LightPoint&, float)> lightPointMovement = [](LightPoint& lightPoint, float deltaTime) {
        float speed = 1.0f;
        float angle = speed * deltaTime;

        lightPoint.Rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle);

        float radius = 7.0f;
        float x = radius * cos(glfwGetTime());
        float z = radius * sin(glfwGetTime());

        lightPoint.Translate(glm::vec3(x - lightPoint.GetPosition().x, 0.0f, z - lightPoint.GetPosition().z));
    };

    Entity rectangularEntity(BaseShapeType::QUAD);
    rectangularEntity.SetTexture(goldOreTexturePath);
    rectangularEntity.Translate(glm::vec3(2.5f, 0.0f, 0.0f));
    rectangularEntity.SetUpdateFunction(rotateEntityAroundY);

    Entity sphereEntity(BaseShapeType::SPHERE);
    sphereEntity.SetTexture(leavesTexturePath);
    sphereEntity.Translate(glm::vec3(-2.5f, 0.0f, 0.0f));
    sphereEntity.SetUpdateFunction(rotateEntityAroundYAndScale);

    Entity cylinderEntity(BaseShapeType::CYLINDER);
    cylinderEntity.SetGradient(BaseColor::Blue(), BaseColor::Magenta());
    cylinderEntity.Translate(glm::vec3(0.0f, 0.0f, 2.5f));
    cylinderEntity.SetUpdateFunction(rotateEntityAroundZAndPublishEvent);

    Entity coneEntity(BaseShapeType::CONE);
    coneEntity.SetColor(BaseColor::Green());
    coneEntity.SetUpdateFunction(rotateEntityAroundZ);

    Entity bottom(BaseShapeType::QUAD);
    bottom.SetColor(BaseColor::LightGray());
    bottom.Translate(glm::vec3(0.0f, -1.0f, 0.0f));
    bottom.Scale(glm::vec3(15.0f, 0.1f, 15.0f));

    engine.LightPoint()->SetUpdateFunction(lightPointMovement);
    engine.LightPoint()->Translate(glm::vec3(7.0f, 7.0f, 7.0f));
    engine.LightPoint()->Scale(glm::vec3(2.0f, 2.0f, 2.0f));
    engine.LightPoint()->Subscribe<ObjectRotated180Event>([&engine](ObjectRotated180Event& event) {
       if (engine.LightPoint()->GetColor() != BaseColor::Red().ToVec4())
       {
           engine.LightPoint()->SetColor(BaseColor::Red());
       }
       else
       {
           engine.LightPoint()->SetColor(BaseColor::White());
       }
    });
    //engine.LightPoint()->SetColor(BaseColor::Pink());
    //engine.LightPoint()->SetColor(BaseColor::Red());

    engine.Camera()->SetPosition(glm::vec3(1.0f, 1.0f, 10.0f));

    engine.AddEntityToRenderer(&rectangularEntity);
    engine.AddEntityToRenderer(&sphereEntity);
    engine.AddEntityToRenderer(&cylinderEntity);
    engine.AddEntityToRenderer(&coneEntity);
    engine.AddEntityToRenderer(&bottom);

    engine.Run();
    return 0;
}