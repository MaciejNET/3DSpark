#ifndef INC_3DSPARK_COLORTEXTURE_H
#define INC_3DSPARK_COLORTEXTURE_H

#include "Texture.h"
#include <glm/glm.hpp>

class ColorTexture : public Texture
{
public:
    explicit ColorTexture(glm::vec4 color) : _color(color) {};
    ~ColorTexture() override = default;

    glm::vec4 GetColor() const { return _color; };
    TextureType GetType() const override { return TextureType::COLOR; };
private:
    glm::vec4 _color{};
};

#endif //INC_3DSPARK_COLORTEXTURE_H
