#include <sstream>
#include <fstream>
#include <iostream>
#include "Managers/TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::pair<GLuint, GLint> TextureManager::LoadTexture(Texture* texture)
{
    switch (texture->GetType())
    {
        case TextureType::COLOR:
            return LoadColorTexture(dynamic_cast<ColorTexture*>(texture));

        case TextureType::IMAGE:
            return LoadImageTexture(dynamic_cast<ImageTexture*>(texture));

        default:
            return { -1, -1 };
    }
}

std::pair<GLuint, GLint> TextureManager::LoadColorTexture(ColorTexture* texture)
{
    std::string vertexShaderSource = ReadFile("../shaders/ColorVertexShader.glsl");
    std::string fragmentShaderSource = ReadFile("../shaders/ColorFragmentShader.glsl");;

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint colorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    return { shaderProgram, colorLocation };
}

std::pair<GLuint, GLint> TextureManager::LoadImageTexture(ImageTexture* texture)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture->GetFilePath().c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture file: " << texture->GetFilePath() << std::endl;
        return { -1, -1 };
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (nrChannels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
    {
        std::cout << "Failed to load texture file: " << texture->GetFilePath() << std::endl;
        return { -1, -1 };
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    texture->SetTextureId(textureId);
    stbi_image_free(data);

    std::string vertexShaderSource = ReadFile("../shaders/ImageVertexShader.glsl");
    std::string fragmentShaderSource = ReadFile("../shaders/ImageFragmentShader.glsl");

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint textureLocation = glGetUniformLocation(shaderProgram, "ourTexture");

    return { shaderProgram, textureLocation };
}

GLuint TextureManager::CompileShader(GLenum shaderType, const std::string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    const char* sourceCStr = shaderSource.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::string shaderTypeStr = (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << shaderTypeStr << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

std::string TextureManager::ReadFile(const std::string& filePath)
{
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open())
    {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream fileContent;
    fileContent << fileStream.rdbuf();
    fileStream.close();

    return fileContent.str();
}

GLuint TextureManager::CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}