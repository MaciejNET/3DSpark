#ifndef INC_3DSPARK_COLOR_H
#define INC_3DSPARK_COLOR_H

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

    glm::vec4 ToVec4() const
    {
        return {r, g, b, a};
    }
};

class BaseColor
{
public:
    static Color White() { return {1.0f, 1.0f, 1.0f, 1.0f}; }
    static Color Black() { return {0.0f, 0.0f, 0.0f, 1.0f}; }
    static Color Red() { return {1.0f, 0.0f, 0.0f, 1.0f}; }
    static Color Green() { return {0.0f, 1.0f, 0.0f, 1.0f}; }
    static Color Blue() { return {0.0f, 0.0f, 1.0f, 1.0f}; }
    static Color Yellow() { return {1.0f, 1.0f, 0.0f, 1.0f}; }
    static Color Cyan() { return {0.0f, 1.0f, 1.0f, 1.0f}; }
    static Color Magenta() { return {1.0f, 0.0f, 1.0f, 1.0f}; }
    static Color Gray() { return {0.5f, 0.5f, 0.5f, 1.0f}; }
    static Color LightGray() { return {0.75f, 0.75f, 0.75f, 1.0f}; }
    static Color DarkGray() { return {0.25f, 0.25f, 0.25f, 1.0f}; }
    static Color Pink() { return {1.0f, 0.4118f, 0.7059f, 1.0f}; }
    static Color Orange() { return {1.0f, 0.5f, 0.0f, 1.0f}; }
    static Color Purple() { return {0.5f, 0.0f, 0.5f, 1.0f}; }
    static Color Brown() { return {0.6f, 0.3f, 0.0f, 1.0f}; }
};

#endif //INC_3DSPARK_COLOR_H
