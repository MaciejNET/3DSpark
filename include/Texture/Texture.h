#ifndef INC_3DSPARK_TEXTURE_H
#define INC_3DSPARK_TEXTURE_H

enum class TextureType
{
    COLOR,
    IMAGE,
    LIGHT,
    GRADIENT
};

class Texture
{
public:
    Texture() = default;
    virtual ~Texture() {};
    virtual TextureType GetType() const = 0;
};

#endif //INC_3DSPARK_TEXTURE_H
