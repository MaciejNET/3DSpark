#ifndef INC_3DSPARK_TEXTUREMANAGER_H
#define INC_3DSPARK_TEXTUREMANAGER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Texture/ColorTexture.h"
#include "../Texture/ImageTexture.h"
#include "../Texture/LightTexture.h"
#include "Texture/GradientTexture.h"

/**
 * @brief Klasa odpowiedzialna za zarządzanie teksturami i ładowanie shaderów.
 */
class TextureManager
{
public:
    /**
     * @brief Metoda LoadTexture ładuje teksturę do pamięci karty graficznej.
     * @param texture wskaźnik na teksturę
     * @return parę zawierającą identyfikator tekstury oraz wektor z wartościami uniformów
     */
    static std::pair<GLuint, std::vector<GLint>> LoadTexture(Texture* texture);
private:
    /**
     * @brief Metoda LoadColorTexture ładuje teksturę kolorową do pamięci karty graficznej.
     * @param texture wskaźnik na teksturę kolorową
     * @return parę zawierającą identyfikator tekstury oraz wektor z wartościami uniformów
     */
    static std::pair<GLuint, std::vector<GLint>> LoadColorTexture(ColorTexture* texture);

    /**
     * @brief Metoda LoadImageTexture ładuje teksturę obrazkową do pamięci karty graficznej.
     * @param texture wskaźnik na teksturę obrazkową
     * @return parę zawierającą identyfikator tekstury oraz wektor z wartościami uniformów
     */
    static std::pair<GLuint, std::vector<GLint>> LoadImageTexture(ImageTexture* texture);

    /**
     * @brief Metoda LoadLightTexture ładuje teksturę światła do pamięci karty graficznej.
     * @param texture wskaźnik na teksturę światła
     * @return parę zawierającą identyfikator tekstury oraz wektor z wartościami uniformów
     */
    static std::pair<GLuint, std::vector<GLint>> LoadLightTexture(LightTexture* texture);

    /**
     * @brief Metoda LoadGradientTexture ładuje teksturę gradientową do pamięci karty graficznej.
     * @param texture wskaźnik na teksturę gradientową
     * @return parę zawierającą identyfikator tekstury oraz wektor z wartościami uniformów
     */
    static std::pair<GLuint, std::vector<GLint>> LoadGradientTexture(GradientTexture* texture);

    /**
     * @brief Metoda CompileShader kompiluje shader.
     * @param shaderType typ shadera
     * @param shaderSource źródło shadera
     * @return identyfikator shadera
     */
    static GLuint CompileShader(GLenum shaderType, const std::string& shaderSource);

    /**
     * @brief Metoda ReadFile wczytuje plik.
     * @param filePath ścieżka do pliku
     * @return zawartość pliku
     */
    static std::string ReadFile(const std::string& filePath);

    /**
     * @brief Metoda CreateShaderProgram tworzy program shaderowy.
     * @param vertexShader identyfikator vertex shadera
     * @param fragmentShader identyfikator fragment shadera
     * @return identyfikator programu shaderowego
     */
    static GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif //INC_3DSPARK_TEXTUREMANAGER_H
