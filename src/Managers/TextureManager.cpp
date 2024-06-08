#include <sstream>
#include <fstream>
#include <iostream>
#include "Managers/TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef __unix__
    const char* colorShaderVertexPath = "../shaders/ColorVertexShader.glsl";
    const char* colorShaderFragmentPath = "../shaders/ColorFragmentShader.glsl";
    const char* imageShaderVertexPath = "../shaders/ImageVertexShader.glsl";
    const char* imageShaderFragmentPath = "../shaders/ImageFragmentShader.glsl";
    const char* lightShaderVertexPath = "../shaders/LightVertexShader.glsl";
    const char* lightShaderFragmentPath = "../shaders/LightFragmentShader.glsl";
    const char* gradientShaderVertexPath = "../shaders/GradientVertexShader.glsl";
    const char* gradientShaderFragmentPath = "../shaders/GradientFragmentShader.glsl";
#elif __aarch64__ || __APPLE__
    const char* colorShaderVertexPath = "../shaders/ColorVertexShader.glsl";
    const char* colorShaderFragmentPath = "../shaders/ColorFragmentShader.glsl";
    const char* imageShaderVertexPath = "../shaders/ImageVertexShader.glsl";
    const char* imageShaderFragmentPath = "../shaders/ImageFragmentShader.glsl";
    const char* lightShaderVertexPath = "../shaders/LightVertexShader.glsl";
    const char* lightShaderFragmentPath = "../shaders/LightFragmentShader.glsl";
    const char* gradientShaderVertexPath = "../shaders/GradientVertexShader.glsl";
    const char* gradientShaderFragmentPath = "../shaders/GradientFragmentShader.glsl";
#elif defined(_WIN32) || defined(_WIN64)
    const char* colorShaderVertexPath = "../../../shaders/ColorVertexShader.glsl";
    const char* colorShaderFragmentPath = "../../../shaders/ColorFragmentShader.glsl";
    const char* imageShaderVertexPath = "../../../shaders/ImageVertexShader.glsl";
    const char* imageShaderFragmentPath = "../../../shaders/ImageFragmentShader.glsl";
    const char* lightShaderVertexPath = "../../../shaders/LightVertexShader.glsl";
    const char* lightShaderFragmentPath = "../../../shaders/LightFragmentShader.glsl";
    const char* gradientShaderVertexPath = "../../../shaders/GradientVertexShader.glsl";
    const char* gradientShaderFragmentPath = "../../../shaders/GradientFragmentShader.glsl";
#endif

std::pair<GLuint, std::vector<GLint>> TextureManager::LoadTexture(Texture* texture)
{
    switch (texture->GetType())
    {
        case TextureType::COLOR:
            return LoadColorTexture(dynamic_cast<ColorTexture*>(texture));

        case TextureType::IMAGE:
            return LoadImageTexture(dynamic_cast<ImageTexture*>(texture));

        case TextureType::LIGHT:
            return LoadLightTexture(dynamic_cast<LightTexture*>(texture));

        case TextureType::GRADIENT:
            return LoadGradientTexture(dynamic_cast<GradientTexture*>(texture));

        default:
            return { -1,  std::vector<GLint>{} };
    }
}

std::pair<GLuint, std::vector<GLint>> TextureManager::LoadColorTexture(ColorTexture* texture)
{
    std::string vertexShaderSource = ReadFile(colorShaderVertexPath);
    std::string fragmentShaderSource = ReadFile(colorShaderFragmentPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint colorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    return { shaderProgram, std::vector<GLint>{colorLocation} };
}

std::pair<GLuint, std::vector<GLint>> TextureManager::LoadImageTexture(ImageTexture* texture)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texture->GetFilePath().c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Failed to load texture file: " << texture->GetFilePath() << std::endl;
        return { -1, std::vector<GLint>{} };
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
        return { -1, std::vector<GLint>{} };
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    texture->SetTextureId(textureId);
    stbi_image_free(data);

    std::string vertexShaderSource = ReadFile(imageShaderVertexPath);
    std::string fragmentShaderSource = ReadFile(imageShaderFragmentPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint textureLocation = glGetUniformLocation(shaderProgram, "ourTexture");

    return { shaderProgram, std::vector<GLint> {textureLocation} };
}

std::pair<GLuint, std::vector<GLint>> TextureManager::LoadLightTexture(LightTexture *texture)
{
    std::string vertexShaderSource = ReadFile(lightShaderVertexPath);
    std::string fragmentShaderSource = ReadFile(lightShaderFragmentPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint colorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    return { shaderProgram, std::vector<GLint> {colorLocation} };
}

std::pair<GLuint, std::vector<GLint>> TextureManager::LoadGradientTexture(GradientTexture *texture)
{
    std::string vertexShaderSource = ReadFile(gradientShaderVertexPath);
    std::string fragmentShaderSource = ReadFile(gradientShaderFragmentPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

    GLint color1Location = glGetUniformLocation(shaderProgram, "color1");
    GLint color2Location = glGetUniformLocation(shaderProgram, "color2");

    return { shaderProgram, std::vector<GLint> {color1Location, color2Location} };

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