#ifndef INC_3DSPARK_LIGHTPOINT_H
#define INC_3DSPARK_LIGHTPOINT_H

#include "Texture/LightTexture.h"
#include "Managers/TextureManager.h"
#include "Entities/Color.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <functional>
#include "Events/Event.h"
#include "Events/EventBus.h"

/**
 * @brief Klasa reprezentująca punkt świetlny
 */
class LightPoint
{
public:
    /**
     * @brief Konstruktor klasy LightPoint
     */
    LightPoint()
    {
        auto texture = new LightTexture(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        SetTexture(texture);
    }

    ~LightPoint() = default;

    /**
     * @brief Rysuje punkt świetlny
     */
    void Draw();

    /**
     * @brief Aktualizuje punkt świetlny
     * @param deltaTime - czas od ostatniej aktualizacji
     */
    void Update(float deltaTime);

    /**
     * @brief Zwraca pozycję punktu świetlnego
     * @return pozycja punktu świetlnego
     */
    glm::vec3 GetPosition() const { return _position; };

    /**
     * @brief Zwraca rotację punktu świetlnego
     * @return rotacja punktu świetlnego
     */
    glm::vec3 GetRotation() const { return _rotation; };

    /**
     * @brief Zwraca skalę punktu świetlnego
     * @return skala punktu świetlnego
     */
    glm::vec3 GetScale() const { return _scale; };

    /**
     * @brief Zwraca color punktu świetlnego
     */
    glm::vec4 GetColor() const { return _texture->GetColor(); };

    /**
     * @brief Ustawia kolory punktu świetlnego
     * @param color - kolor punktu świetlnego
     */
    void SetColor(const Color& color)
    {
        auto texture = new LightTexture(glm::vec4(color.r, color.g, color.b, color.a));
        SetTexture(texture);
    }

    /**
     * Metoda do ustawiania widoku kamery
     * @param view macierz widoku kamery
     * @param projection macierz projekcji kamery
     */
    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection)
    {
        _viewMatrix = view;
        _projectionMatrix = projection;
    }

    /**
     * Metoda przesuwająca obiekt
     * @param translation wektor przesunięcia
     */
    void Translate(const glm::vec3& translation) { _position += translation; UpdateModelMatrix(); };

    /**
     * Metoda obracająca obiekt
     * @param axis oś obrotu
     * @param angle kąt obrotu
     */
    void Rotate(const glm::vec3& axis, float angle) { _rotation += glm::degrees(axis * angle); UpdateModelMatrix(); };

    /**
     * Metoda skalująca obiekt
     * @param scale wektor skalowania
     */
    void Scale(const glm::vec3& scale) { _scale *= scale; UpdateModelMatrix(); };

    /**
     * Metoda ustawiająca funkcję aktualizującą obiekt
     * @param function funkcja aktualizująca obiekt
     */
    void SetUpdateFunction(std::function<void(LightPoint&, float deltaTime)> function)
    {
        updateFunction = std::move(function);
    }

    /**
     * Metoda do subskrybowania zdarzeń
     * @tparam TEvent typ zdarzenia
     * @param callback funkcja wywoływana przy zdarzeniu
     */
    template<typename TEvent, typename = std::enable_if_t<std::is_base_of_v<Event, TEvent>>>
    void Subscribe(std::function<void(TEvent&)> callback)
    {
        EventBus::Subscribe(callback);
    }

    /**
     * Metoda do odsubskrybowania zdarzeń
     * @tparam TEvent typ zdarzenia
     */
    template<typename TEvent, typename = std::enable_if_t<std::is_base_of_v<Event, TEvent>>>
    void Unsubscribe()
    {
        EventBus::Unsubscribe<TEvent>();
    }

protected:
    /**
     * Metoda aktualizująca macierz modelu
     */
    void UpdateModelMatrix()
    {
        _modelMatrix = glm::mat4(1.0f);
        _modelMatrix = glm::translate(_modelMatrix, _position);
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        _modelMatrix = glm::scale(_modelMatrix, _scale);
    }

    /**
     * Metoda ustawiająca teksturę(materiał) obiektu
     * @param texture wskaźnik na teksturę
     */
    void SetTexture(LightTexture* texture)
    {
        delete _texture;
        _texture = texture;
        std::tie(_shaderProgram, _uniformLocations) = TextureManager::LoadTexture(_texture);
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
