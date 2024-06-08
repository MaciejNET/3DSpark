#include "../include/Entities/ConeEntity.h"
#include "../include/Managers/InputManager.h"

void ConeEntity::Draw()
{
    Entity::Draw();

    const int segments = 36;
    const float radius = 0.5f;
    const float height = 1.0f;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    for (int i = 0; i <= segments; ++i)
    {
        float angle = (2.0f * M_PI / segments) * i;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);

        vertices.push_back(0.5f + cos(angle) / 2.0f);
        vertices.push_back(0.5f + sin(angle) / 2.0f);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);
    }

    vertices.push_back(0.0f);
    vertices.push_back(height);
    vertices.push_back(0.0f);

    vertices.push_back(0.5f);
    vertices.push_back(0.5f);

    vertices.push_back(0.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);

    for (int i = 0; i < segments; ++i)
    {
        indices.push_back(i);
        indices.push_back((i + 1) % segments);
        indices.push_back(segments);
    }

    for (int i = 0; i < segments; ++i)
    {
        indices.push_back(i);
        indices.push_back((i + 1) % segments);
        indices.push_back(segments + 1);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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

void ConeEntity::Update(float deltaTime)
{
}