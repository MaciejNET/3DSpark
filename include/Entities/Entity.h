#ifndef INC_3DSPARK_ENTITY_H
#define INC_3DSPARK_ENTITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
#include "../Texture/Texture.h"
#include "../Texture/ColorTexture.h"
#include "../Managers/TextureManager.h"
#include "BaseShapes.h"
#include "Color.h"
#include "Events/Event.h"
#include "Events/EventBus.h"

class Entity
{
public:
    explicit Entity(BaseShapeType shape);
    ~Entity();

    void Draw();

    void Update(float deltaTime);

    glm::vec3 GetPosition() const { return _position; };
    glm::vec3 GetRotation() const { return _rotation; };
    glm::vec3 GetScale() const { return _scale; };


    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection);
    void SetLightColor(const glm::vec4& color);
    void SetLightPosition(const glm::vec3& position);
    void SetCameraPosition(const glm::vec3& position);
    void SetUpdateFunction(std::function<void(Entity&, float deltaTime)> function);
    void SetLightingEnabled(bool isEnabled);
    void SetShadingEnabled(bool isEnabled);

    void SetColor(const Color& color);
    void SetTexture(const std::string& texturePath);
    void SetGradient(const Color& startColor, const Color& endColor);

    void Translate(const glm::vec3& translation);
    void Rotate(const glm::vec3& axis, float angle);
    void Scale(const glm::vec3& scale);

    template<typename TEvent, typename = std::enable_if_t<std::is_base_of_v<Event, TEvent>>>
    void Subscribe(std::function<void(TEvent&)> callback)
    {
        EventBus::Subscribe(callback);
    }

    template<typename TEvent, typename = std::enable_if_t<std::is_base_of_v<Event, TEvent>>>
    void Unsubscribe()
    {
        EventBus::Unsubscribe<TEvent>();
    }

protected:
    void UpdateModelMatrix();
    void SetTexture(Texture* texture);

protected:
    glm::vec3 _position{};
    glm::vec3 _rotation{};
    glm::vec3 _scale{1.0f};
    Texture* _texture{};
    glm::mat4 _modelMatrix{1.0f};
    GLuint _shaderProgram{};
    std::vector<GLint> _uniformLocations{};
    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};
    glm::vec4 _lightColor{1.0f};
    glm::vec3 _lightPosition{0.0f};
    glm::vec3 _cameraPosition{0.0f};
    bool _isLightingEnabled{true};
    bool _isShadingEnabled{true};
    std::function<void(Entity&, float deltaTime)> _updateFunction;
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
};

#endif //INC_3DSPARK_ENTITY_H
