#include "../../include/Entities/BaseShapes.h"

std::tuple<std::vector<float>, std::vector<unsigned int>> BaseShapes::Quad()
{
    std::vector<float> vertices = {
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 0.0f,       0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,       0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 0.0f,       0.0f, 0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f,       0.0f, 0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f,       0.0f, 0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f, 0.0f, -1.0f,

            0.5f,  0.5f,  0.5f,   1.0f, 0.0f,       1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   0.0f, 0.0f,       1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f,       1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f,       1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 1.0f,       1.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f,       1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,   1.0f, 1.0f,       0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,   1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,   1.0f, 1.0f,       0.0f, -1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,   1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f, 0.0f,
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,
            3, 4, 5,

            6, 7, 8,
            9, 10, 11,

            12, 13, 14,
            15, 16, 17,

            18, 19, 20,
            21, 22, 23,

            24, 25, 26,
            27, 28, 29,

            30, 31, 32,
            33, 34, 35
    };

    return std::make_tuple(vertices, indices);
}

std::tuple<std::vector<float>, std::vector<unsigned int>> BaseShapes::Sphere()
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

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
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

    return std::make_tuple(vertices, indices);
}

std::tuple<std::vector<float>, std::vector<unsigned int>> BaseShapes::Cylinder()
{
    const int segments = 36;
    const float radius = 0.5f;
    const float height = 1.0f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= segments; ++i)
    {
        float angle = (2.0f * M_PI / segments) * i;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(height / 2);
        vertices.push_back(z);

        vertices.push_back(0.5f + cos(angle) / 2.0f);
        vertices.push_back(0.5f + sin(angle) / 2.0f);

        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
    }

    for (int i = 0; i <= segments; ++i)
    {
        float angle = (2.0f * M_PI / segments) * i;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(-height / 2);
        vertices.push_back(z);

        vertices.push_back(0.5f + cos(angle) / 2.0f); // u
        vertices.push_back(0.5f + sin(angle) / 2.0f); // v

        vertices.push_back(0.0f);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
    }

    for (int i = 0; i <= segments; ++i)
    {
        float angle = (2.0f * M_PI / segments) * i;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(height / 2);
        vertices.push_back(z);
        vertices.push_back((float)i / segments);
        vertices.push_back(1.0f);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);

        vertices.push_back(x);
        vertices.push_back(-height / 2);
        vertices.push_back(z);
        vertices.push_back((float)i / segments);
        vertices.push_back(0.0f);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);
    }

    for (int i = 0; i < segments; ++i)
    {
        indices.push_back(i);
        indices.push_back((i + 1) % segments);
        indices.push_back(segments);
    }

    int bottomCircleStartIndex = segments + 1;
    for (int i = 0; i < segments; ++i)
    {
        indices.push_back(bottomCircleStartIndex + i);
        indices.push_back(bottomCircleStartIndex + ((i + 1) % segments));
        indices.push_back(bottomCircleStartIndex + segments);
    }

    for (int i = 0; i < segments; ++i)
    {
        int offset = segments * 2 + 2;
        indices.push_back(offset + i * 2);
        indices.push_back(offset + (i * 2 + 2) % (segments * 2));
        indices.push_back(offset + (i * 2 + 3) % (segments * 2));

        indices.push_back(offset + i * 2);
        indices.push_back(offset + (i * 2 + 3) % (segments * 2));
        indices.push_back(offset + (i * 2 + 1) % (segments * 2));
    }

    return std::make_tuple(vertices, indices);
}

std::tuple<std::vector<float>, std::vector<unsigned int>> BaseShapes::Cone()
{
    const int segments = 36;
    const float radius = 0.5f;
    const float height = 1.0f;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

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

    return std::make_tuple(vertices, indices);
}