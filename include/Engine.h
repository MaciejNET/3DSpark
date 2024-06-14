#ifndef INC_3DSPARK_ENGINE_H
#define INC_3DSPARK_ENGINE_H

#include "Entities/Entity.h"
#include "Renderer.h"

/**
 * @brief Klasa silnika
 */
class Engine
{
public:
    /**
     * @brief Konstruktor klasy Engine
     * @param width Szerokość okna
     * @param height Wysokość okna
     * @param title Tytuł okna
     */
    Engine(int width, int height, const char* title);

    /**
     * @brief Konstruktor klasy Engine
     * @param width Szerokość okna
     * @param height Wysokość okna
     * @param title Tytuł okna
     * @param targetFps Docelowa liczba klatek na sekundę
     */
    Engine(int width, int height, const char* title, float targetFps);
    ~Engine();

    /**
     * @brief Metoda uruchamiająca silnik
     */
    void Run();

    /**
     * @brief Metoda dodająca obiekt do renderera
     */
    void AddEntityToRenderer(Entity* entity);

    /**
     * @brief Metoda usuwająca obiekt z renderera
     */
    void RemoveEntityFromRenderer(Entity* entity);

    /**
     * @brief Metoda czyszcząca obiekty z renderera
     */
    void ClearEntitiesFromRenderer();

    /**
     * @brief Metoda ustawiająca docelową liczbę klatek na sekundę
     * @param targetFps Docelowa liczba klatek na sekundę
     */
    void SetTargetFps(float targetFps);

    /**
     * @brief Metoda włączająca kursor
     */
    void TurnOnCursor();

    /**
     * @brief Metoda wyłączająca kursor
     */
    void TurnOffCursor();

    /**
     * @brief Metoda zwracająca wskaźnik na kamerę
     * @return Wskaźnik na kamerę
     */
    Camera* Camera() const { return _renderer->GetCamera(); };

    /**
     * @brief Metoda zwracająca wskaźnik na światło
     * @return Wskaźnik na światło
     */
    LightPoint* LightPoint() const { return _renderer->GetLightPoint(); };

private:
    float _targetFps{};
    Renderer* _renderer;
    float _deltaTime{};
    float _lastFrame{};
    float _fps{};
    bool _isLightingEnabled{true};
    bool _isShadingEnabled{true};
};

#endif //INC_3DSPARK_ENGINE_H
