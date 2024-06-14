#ifndef INC_3DSPARK_LIGHTTEXTURE_H
#define INC_3DSPARK_LIGHTTEXTURE_H

#include "Texture.h"
#include "glm/vec4.hpp"
#include "../Managers/WindowManager.h"

/**
 * @brief Tekstura światła
 */
class LightTexture : public Texture
{
public:
    explicit LightTexture(glm::vec4 color) : _color(color) {};
    ~LightTexture() override = default;

    glm::vec4 GetColor() const { return _color; };
    TextureType GetType() const override { return TextureType::LIGHT; };
private:
    glm::vec4 _color{};
};

#endif //INC_3DSPARK_LIGHTTEXTURE_H
