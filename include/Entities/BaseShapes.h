#ifndef INC_3DSPARK_BASESHAPES_H
#define INC_3DSPARK_BASESHAPES_H

#include <vector>
#include <tuple>

#if defined(_WIN32) || defined(_WIN64)
    #define M_PI 3.14
#endif

enum class BaseShapeType
{
    QUAD,
    SPHERE,
    CYLINDER,
    CONE
};

class BaseShapes
{
public:
    static std::tuple<std::vector<float>, std::vector<unsigned int>> Quad();
    static std::tuple<std::vector<float>, std::vector<unsigned int>> Sphere();
    static std::tuple<std::vector<float>, std::vector<unsigned int>> Cylinder();
    static std::tuple<std::vector<float>, std::vector<unsigned int>> Cone();
};

#endif //INC_3DSPARK_BASESHAPES_H
