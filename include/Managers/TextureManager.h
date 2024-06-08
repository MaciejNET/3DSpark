#ifndef INC_3DSPARK_TEXTUREMANAGER_H
#define INC_3DSPARK_TEXTUREMANAGER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Texture/ColorTexture.h"
#include "../Texture/ImageTexture.h"
#include "../Texture/LightTexture.h"
#include "Texture/GradientTexture.h"

class TextureManager
{
public:
    static std::pair<GLuint, std::vector<GLint>> LoadTexture(Texture* texture);
private:
    static std::pair<GLuint, std::vector<GLint>> LoadColorTexture(ColorTexture* texture);
    static std::pair<GLuint, std::vector<GLint>> LoadImageTexture(ImageTexture* texture);
    static std::pair<GLuint, std::vector<GLint>> LoadLightTexture(LightTexture* texture);
    static std::pair<GLuint, std::vector<GLint>> LoadGradientTexture(GradientTexture* texture);
    static GLuint CompileShader(GLenum shaderType, const std::string& shaderSource);
    static std::string ReadFile(const std::string& filePath);
    static GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif //INC_3DSPARK_TEXTUREMANAGER_H
