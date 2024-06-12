#include "../../include/Entities/Entity.h"

Entity::Entity(BaseShapeType shape)
{
    _modelMatrix = glm::mat4(1.0f);
    _isLightingEnabled = true;
    _isShadingEnabled = true;
    _cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    _lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    _lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    auto texture = new ColorTexture(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    SetTexture(texture);

    switch (shape)
    {
        case BaseShapeType::CONE:
            std::tie(_vertices, _indices) = BaseShapes::Cone();
            break;

        case BaseShapeType::QUAD:
            std::tie(_vertices, _indices) = BaseShapes::Quad();
            break;

        case BaseShapeType::CYLINDER:
            std::tie(_vertices, _indices) = BaseShapes::Cylinder();
            break;

        case BaseShapeType::SPHERE:
            std::tie(_vertices, _indices) = BaseShapes::Sphere();
            break;

        default:
            throw std::runtime_error("Invalid shape type");
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void Entity::Draw()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glUseProgram(_shaderProgram);

    GLint viewLoc = glGetUniformLocation(_shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));

    GLint projLoc = glGetUniformLocation(_shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

    switch (_texture->GetType())
    {
        case TextureType::COLOR:
            glUniform4fv(_uniformLocations[0], 1, &dynamic_cast<ColorTexture*>(_texture)->GetColor()[0]);
            break;

        case TextureType::IMAGE:
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, dynamic_cast<ImageTexture*>(_texture)->GetTextureId());
            glUniform1i(_uniformLocations[0], 0);
            break;

        case TextureType::GRADIENT:
            glUniform4fv(_uniformLocations[0], 1, &dynamic_cast<GradientTexture*>(_texture)->GetColor1()[0]);
            glUniform4fv(_uniformLocations[1], 1, &dynamic_cast<GradientTexture*>(_texture)->GetColor2()[0]);
            break;

        default:
            break;
    }

    GLint lightColorLocation = glGetUniformLocation(_shaderProgram, "lightColor");
    glUniform4fv(lightColorLocation, 1, glm::value_ptr(_lightColor));

    GLint lightPositionLocation = glGetUniformLocation(_shaderProgram, "lightPos");
    glUniform3fv(lightPositionLocation, 1, glm::value_ptr(_lightPosition));

    GLint cameraPositionLocation = glGetUniformLocation(_shaderProgram, "cameraPos");
    glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(_cameraPosition));

    GLint isLightingEnabledLocation = glGetUniformLocation(_shaderProgram, "isLightingEnabled");
    glUniform1i(isLightingEnabledLocation, _isLightingEnabled);

    GLint isShadingEnabledLocation = glGetUniformLocation(_shaderProgram, "isShadingEnabled");
    glUniform1i(isShadingEnabledLocation, _isShadingEnabled);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    GLint modelLoc = glGetUniformLocation(_shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Entity::Update(float deltaTime)
{
    if (_updateFunction)
    {
        _updateFunction(*this, deltaTime);
    }
}

void Entity::SetTexture(Texture* texture)
{
    delete _texture;
    _texture = texture;
    std::tie(_shaderProgram, _uniformLocations) = TextureManager::LoadTexture(_texture);
}

void Entity::SetCameraMatrices(const glm::mat4 &view, const glm::mat4 &projection)
{
    _viewMatrix = view;
    _projectionMatrix = projection;
}

void Entity::SetLightColor(const glm::vec4& color)
{
    _lightColor = color;
}

void Entity::SetLightPosition(const glm::vec3& position)
{
    _lightPosition = position;
}

void Entity::SetCameraPosition(const glm::vec3& position)
{
    _cameraPosition = position;
}

void Entity::SetUpdateFunction(std::function<void(Entity&, float deltaTime)> function)
{
    _updateFunction = std::move(function);
}

void Entity::SetLightingEnabled(bool isEnabled)
{
    _isLightingEnabled = isEnabled;
}

void Entity::SetShadingEnabled(bool isEnabled)
{
    _isShadingEnabled = isEnabled;
}

void Entity::Translate(const glm::vec3& translation)
{
    _position += translation;
    UpdateModelMatrix();
}

void Entity::Rotate(const glm::vec3& axis, float angle)
{
    _rotation += glm::degrees(axis * angle); UpdateModelMatrix();
}

void Entity::Scale(const glm::vec3& scale)
{
    _scale *= scale; UpdateModelMatrix();
}

void Entity::UpdateModelMatrix()
{
    _modelMatrix = glm::mat4(1.0f);
    _modelMatrix = glm::translate(_modelMatrix, _position);
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    _modelMatrix = glm::scale(_modelMatrix, _scale);
}

Entity::~Entity()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete _texture;
}