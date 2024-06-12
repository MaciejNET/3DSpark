#ifndef INC_3DSPARK_LIGHTPOINT_H
#define INC_3DSPARK_LIGHTPOINT_H

#include "Texture/LightTexture.h"
#include "Managers/TextureManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <functional>

class LightPoint
{
public:
    LightPoint()
    {
        auto texture = new LightTexture(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        SetTexture(texture);
    }

    ~LightPoint() = default;
    void Draw();
    void Update(float deltaTime);
    glm::vec3 GetPosition() const { return _position; };
    glm::vec3 GetRotation() const { return _rotation; };
    glm::vec3 GetScale() const { return _scale; };
    glm::vec4 GetColor() const { return _texture->GetColor(); };
    void SetTexture(LightTexture* texture)
    {
        delete _texture;
        _texture = texture;
        std::tie(_shaderProgram, _uniformLocations) = TextureManager::LoadTexture(_texture);
    }

    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection)
    {
        _viewMatrix = view;
        _projectionMatrix = projection;
    }
    void Translate(const glm::vec3& translation) { _position += translation; UpdateModelMatrix(); };
    void Rotate(const glm::vec3& axis, float angle) { _rotation += glm::degrees(axis * angle); UpdateModelMatrix(); };
    void Scale(const glm::vec3& scale) { _scale *= scale; UpdateModelMatrix(); };

    void SetUpdateFunction(std::function<void(LightPoint&, float deltaTime)> function)
    {
        updateFunction = std::move(function);
    }

protected:
    void UpdateModelMatrix()
    {
        _modelMatrix = glm::mat4(1.0f);
        _modelMatrix = glm::translate(_modelMatrix, _position);
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        _modelMatrix = glm::scale(_modelMatrix, _scale);
    }

protected:
    glm::vec3 _position{};
    glm::vec3 _rotation{};
    glm::vec3 _scale{1.0f};
    LightTexture* _texture{};
    glm::mat4 _modelMatrix{1.0f};
    GLuint _shaderProgram{};
    std::vector<GLint> _uniformLocations{};
    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};
    std::function<void(LightPoint&, float deltaTime)> updateFunction;
};

#endif //INC_3DSPARK_LIGHTPOINT_H
