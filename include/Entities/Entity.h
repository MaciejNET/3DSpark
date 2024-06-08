#ifndef INC_3DSPARK_ENTITY_H
#define INC_3DSPARK_ENTITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Texture/Texture.h"
#include "../Texture/ColorTexture.h"
#include "../Managers/TextureManager.h"

#if defined(_WIN32) || defined(_WIN64)
    #define M_PI 3.14
#endif

class Entity
{
public:
    Entity()
    {
        auto texture = new ColorTexture(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        SetTexture(texture);
    }
    virtual ~Entity() { delete _texture; };

    virtual void Draw()
    {
        glUseProgram(_shaderProgram);

        GLint viewLoc = glGetUniformLocation(_shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));

        GLint projLoc = glGetUniformLocation(_shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

        switch (_texture->GetType())
        {
            case TextureType::COLOR:
                glUniform4fv(_uniformLocations[0], 1, &dynamic_cast<ColorTexture*>(_texture)->GetColor()[0]);
                break;

            case TextureType::IMAGE:
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, dynamic_cast<ImageTexture*>(_texture)->GetTextureId());
                glUniform1i(_uniformLocations[0], 0);
                break;

            case TextureType::GRADIENT:
                glUniform4fv(_uniformLocations[0], 1, &dynamic_cast<GradientTexture*>(_texture)->GetColor1()[0]);
                glUniform4fv(_uniformLocations[1], 1, &dynamic_cast<GradientTexture*>(_texture)->GetColor2()[0]);
                break;

            default:
                break;
        }

        GLint lightColorLocation = glGetUniformLocation(_shaderProgram, "lightColor");
        glUniform4fv(lightColorLocation, 1, glm::value_ptr(_lightColor));

        GLint lightPositionLocation = glGetUniformLocation(_shaderProgram, "lightPos");
        glUniform3fv(lightPositionLocation, 1, glm::value_ptr(_lightPosition));

        GLint cameraPositionLocation = glGetUniformLocation(_shaderProgram, "cameraPos");
        glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(_cameraPosition));
    }
    virtual void Update(float deltaTime) = 0;

    glm::vec3 GetPosition() const { return _position; };
    glm::vec3 GetRotation() const { return _rotation; };
    glm::vec3 GetScale() const { return _scale; };

    void SetTexture(Texture* texture)
    {
        delete _texture;
        _texture = texture;
        std::tie(_shaderProgram, _uniformLocations) = TextureManager::LoadTexture(_texture);
    };

    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection)
    {
        _viewMatrix = view;
        _projectionMatrix = projection;
    }

    void SetLightColor(const glm::vec4& color)
    {
        _lightColor = color;
    }

    void SetLightPosition(const glm::vec3& position)
    {
        _lightPosition = position;
    }

    void SetCameraPosition(const glm::vec3& position)
    {
        _cameraPosition = position;
    }

    void Translate(const glm::vec3& translation) { _position += translation; UpdateModelMatrix(); };
    void Rotate(const glm::vec3& axis, float angle) { _rotation += glm::degrees(axis * angle); UpdateModelMatrix(); };
    void Scale(const glm::vec3& scale) { _scale *= scale; UpdateModelMatrix(); };

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
    Texture* _texture{};
    glm::mat4 _modelMatrix{1.0f};
    GLuint _shaderProgram{};
    std::vector<GLint> _uniformLocations{};
    glm::mat4 _viewMatrix{1.0f};
    glm::mat4 _projectionMatrix{1.0f};
    glm::vec4 _lightColor{1.0f};
    glm::vec3 _lightPosition{0.0f};
    glm::vec3 _cameraPosition{0.0f};
};

#endif //INC_3DSPARK_ENTITY_H
