#ifndef INC_3DSPARK_GRADIENTTEXTURE_H
#define INC_3DSPARK_GRADIENTTEXTURE_H

#include "Texture.h"
#include "glm/vec4.hpp"

class GradientTexture : public Texture
{
public:
    GradientTexture(glm::vec4 color1, glm::vec4 color2) : _color1(color1), _color2(color2) {};
    ~GradientTexture() override = default;
    TextureType GetType() const override { return TextureType::GRADIENT; }
    glm::vec4 GetColor1() const { return _color1; }
    glm::vec4 GetColor2() const { return _color2; }

private:
    glm::vec4 _color1{0.0f, 0.0f, 0.0f, 1.0f};
    glm::vec4 _color2{0.0f, 0.0f, 0.0f, 1.0f};
};

#endif //INC_3DSPARK_GRADIENTTEXTURE_H
