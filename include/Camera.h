#ifndef INC_3DSPARK_CAMERA_H
#define INC_3DSPARK_CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(int width, int height);
    void Update();
    void Rotate(float x, float y);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetPosition() const;
    void SetPosition(glm::vec3 position);
    void SetOrientation(glm::vec3 orientation);
    void SetUp(glm::vec3 up);
    void SetSpeed(float speed);
    void SetSensitivity(float sensitivity);
    void SetWidth(int width);
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
