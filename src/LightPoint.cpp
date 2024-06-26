#include "../include/LightPoint.h"

void LightPoint::Draw()
{
    const int segments = 36;
    const int rings = 18;
    const float radius = 0.5f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= rings; ++i)
    {
        for (int j = 0; j <= segments; ++j)
        {
            float y = cos((M_PI / rings) * i);
            float x = cos((2.0f * M_PI / segments) * j) * sin((M_PI / rings) * i);
            float z = sin((2.0f * M_PI / segments) * j) * sin((M_PI / rings) * i);

            vertices.push_back(radius * x);
            vertices.push_back(radius * y);
            vertices.push_back(radius * z);

            vertices.push_back((float)j / segments);
            vertices.push_back((float)i / rings);
        }
    }

    for (int i = 0; i < rings; ++i)
    {
        for (int j = 0; j < segments; ++j)
        {
            indices.push_back(i * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j + 1);

            indices.push_back(i * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j + 1);
            indices.push_back(i * (segments + 1) + j + 1);
        }
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glUseProgram(_shaderProgram);

    GLint viewLoc = glGetUniformLocation(_shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));

    GLint projLoc = glGetUniformLocation(_shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

    glUniform4fv(_uniformLocations[0], 1, &_texture->GetColor()[0]);

    GLint modelLoc = glGetUniformLocation(_shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void LightPoint::Update(float deltaTime)
{
    if (updateFunction)
    {
        updateFunction(*this, deltaTime);
    }
}