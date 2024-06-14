#ifndef INC_3DSPARK_RENDERER_H
#define INC_3DSPARK_RENDERER_H

#include "Entities/Entity.h"
#include "Managers/WindowManager.h"
#include "Camera.h"
#include "LightPoint.h"
#include <vector>

/**
 * @brief Klasa odpowiedzialna za renderowanie obiektów
 */
class Renderer
{
public:
    Renderer() : _camera(new Camera(WindowManager::GetWidth(), WindowManager::GetHeight())),
        _lightPoint(new LightPoint())
    {
    }

    ~Renderer() = default;

    /**
     * @brief Metoda renderująca obiekty
     * @param deltaTime Czas od ostatniej klatki
     * @param isLightingEnabled Czy włączone jest oświetlenie
     * @param isShadingEnabled Czy włączone jest cieniowanie
     */
    void Render(float deltaTime, bool isLightingEnabled, bool isShadingEnabled);

    /**
     * @brief Metoda dodająca obiekt do renderera
     * @param entity Obiekt do dodania
     */
    void AddEntity(Entity* entity);

    /**
     * @brief Metoda usuwająca obiekt z renderera
     * @param entity Obiekt do usunięcia
     */
    void RemoveEntity(Entity* entity);

    /**
     * @brief Metoda czyszcząca obiekty z renderera
     */
    void ClearEntities();

    /**
     * @brief Metoda zwracająca kamerę
     * @return Kamera
     */
    Camera* GetCamera() const { return _camera; };

    /**
     * @brief Metoda zwracająca światło
     * @return Światło
     */
    LightPoint* GetLightPoint() const { return _lightPoint; };

private:
    std::vector<Entity*> _entities;
    Camera* _camera;
    LightPoint* _lightPoint;
};

#endif //INC_3DSPARK_RENDERER_H
