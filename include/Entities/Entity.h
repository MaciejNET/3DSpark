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

/**
 * Klasa reprezentująca obiekt w przestrzeni 3D
 */
class Entity
{
public:
    /**
     * Konstruktor przyjmujący kształt obiektu
     */
    explicit Entity(BaseShapeType shape);
    ~Entity();

    /**
     * Metoda rysująca obiekt
     */
    void Draw();

    /**
     * Metoda aktualizująca obiekt
     * @param deltaTime czas od ostatniej aktualizacji
     */
    void Update(float deltaTime);

    /**
     * Metoda zwracająca pozycję obiektu
     * @return pozycja obiektu
     */
    glm::vec3 GetPosition() const { return _position; };

    /**
     * Metoda zwracająca rotację obiektu
     * @return rotacja obiektu
     */
    glm::vec3 GetRotation() const { return _rotation; };

    /**
     * Metoda zwracająca skalę obiektu
     * @return skala obiektu
     */
    glm::vec3 GetScale() const { return _scale; };

    /**
     * Metoda do ustawiania widoku kamery
     * @param view macierz widoku kamery
     * @param projection macierz projekcji kamery
     */
    void SetCameraMatrices(const glm::mat4& view, const glm::mat4& projection);

    /**
     * Metoda ustawiająca kolor światła
     * @param color kolor światła
     */
    void SetLightColor(const glm::vec4& color);

    /**
     * Metoda ustawiająca pozycję światła
     * @param position pozycja światła
     */
    void SetLightPosition(const glm::vec3& position);

    /**
     * Metoda ustawiająca pozycję kamery
     * @param position pozycja kamery
     */
    void SetCameraPosition(const glm::vec3& position);

    /**
     * Metoda ustawiająca funkcję aktualizującą obiekt
     * @param function funkcja aktualizująca obiekt
     */
    void SetUpdateFunction(std::function<void(Entity&, float deltaTime)> function);

    /**
     * Metoda ustawiająca czy oświetlenie wpływa na obiekt
     * @param isEnabled czy oświetlenie jest włączone
     */
    void SetLightingEnabled(bool isEnabled);

    /**
     * Metoda ustawiająca czy cieniowanie wpływa na obiekt
     * @param isEnabled czy cieniowanie jest włączone
     */
    void SetShadingEnabled(bool isEnabled);

    /**
     * Metoda ustawiająca kolor obiektu
     * @param color kolor obiektu
     */
    void SetColor(const Color& color);

    /**
     * Metoda ustawiająca teksturę obiektu
     * @param texturePath ścieżka do tekstury
     */
    void SetTexture(const std::string& texturePath);

    /**
     * Metoda ustawiająca gradient kolorów obiektu
     * @param startColor kolor początkowy
     * @param endColor kolor końcowy
     */
    void SetGradient(const Color& startColor, const Color& endColor);

    /**
     * Metoda przesuwająca obiekt
     * @param translation wektor przesunięcia
     */
    void Translate(const glm::vec3& translation);

    /**
     * Metoda obracająca obiekt
     * @param axis oś obrotu
     * @param angle kąt obrotu
     */
    void Rotate(const glm::vec3& axis, float angle);

    /**
     * Metoda skalująca obiekt
     * @param scale wektor skali
     */
    void Scale(const glm::vec3& scale);

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
    void UpdateModelMatrix();

    /**
     * Metoda ustawiająca teksturę(materiał) obiektu
     * @param texture wskaźnik na teksturę
     */
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
