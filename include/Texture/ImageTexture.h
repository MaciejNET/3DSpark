#ifndef INC_3DSPARK_IMAGETEXTURE_H
#define INC_3DSPARK_IMAGETEXTURE_H

#include "Texture.h"
#include <string>
#include <utility>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ImageTexture : public Texture
{
public:
    explicit ImageTexture(std::string  filePath) : _filePath(std::move(filePath)) {};
    ~ImageTexture() override = default;

    TextureType GetType() const override { return TextureType::IMAGE; };
    const std::string& GetFilePath() const { return _filePath; };
    GLuint GetTextureId() const { return _textureId; };

    void SetTextureId(GLuint textureId) { _textureId = textureId; };

private:
    std::string _filePath{};
    GLuint _textureId{};
};

#endif //INC_3DSPARK_IMAGETEXTURE_H
