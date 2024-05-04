#ifndef INC_3DSPARK_TEXTUREMANAGER_H
#define INC_3DSPARK_TEXTUREMANAGER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Texture/ColorTexture.h"
#include "../Texture/ImageTexture.h"

class TextureManager
{
public:
    static std::pair<GLuint, GLint> LoadTexture(Texture* texture);
private:
    static std::pair<GLuint, GLint> LoadColorTexture(ColorTexture* texture);
    static std::pair<GLuint, GLint> LoadImageTexture(ImageTexture* texture);
    static GLuint CompileShader(GLenum shaderType, const std::string& shaderSource);
    static std::string ReadFile(const std::string& filePath);
    static GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif //INC_3DSPARK_TEXTUREMANAGER_H
