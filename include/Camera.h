#ifndef INC_3DSPARK_CAMERA_H
#define INC_3DSPARK_CAMERA_H

#include <glm/glm.hpp>

/**
 * @brief Kamera
 */
class Camera
{
public:
    /**
     * @brief Konstruktor
     * @param width Szerokość okna
     * @param height Wysokość okna
     */
    Camera(int width, int height);

    /**
     * @brief Metoda aktualizująca kamerę
     */
    void Update();

    /**
     * @brief Metoda obracająca kamerę
     * @param x Przesunięcie w osi x
     * @param y Przesunięcie w osi y
     */
    void Rotate(float x, float y);

    /**
     * @brief Metoda zwracająca macierz widoku
     * @return Macierz widoku
     */
    glm::mat4 GetViewMatrix();

    /**
     * @brief Metoda zwracająca macierz projekcji
     * @return Macierz projekcji
     */
    glm::mat4 GetProjectionMatrix() const;

    /**
     * @brief Metoda zwracająca pozycję kamery
     * @return Pozycja kamery
     */
    glm::vec3 GetPosition() const;

    /**
     * @brief Metoda ustawiająca pozycję kamery
     * @param position Pozycja kamery
     */
    void SetPosition(glm::vec3 position);

    /**
     * @brief Metoda ustawiająca orientację kamery
     * @param orientation Orientacja kamery
     */
    void SetOrientation(glm::vec3 orientation);

    /**
     * @brief Metoda ustawiająca górę kamery
     * @param up Góra kamery
     */
    void SetUp(glm::vec3 up);

    /**
     * @brief Metoda ustawiająca prędkość kamery
     * @param speed Prędkość kamery
     */
    void SetSpeed(float speed);

    /**
     * @brief Metoda ustawiająca czułość kamery
     * @param sensitivity Czułość kamery
     */
    void SetSensitivity(float sensitivity);

    /**
     * @brief Metoda ustawiająca szerokość okna
     * @param width Szerokość okna
     */
    void SetWidth(int width);

    /**
     * @brief Metoda ustawiająca wysokość okna
     * @param height Wysokość okna
     */
    void SetHeight(int height);
private:
    glm::vec3 _position{0.0f, 0.0f, 0.0f};
    glm::vec3 _orientation{0.0f, 0.0f, -1.0f};
    glm::vec3 _up{0.0f, 1.0f, 0.0f};
    int _width{};
    int _height{};
    float _speed{0.01f};
    float _sensitivity{15.0f};
};

#endif //INC_3DSPARK_CAMERA_H
