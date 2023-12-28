#ifndef HEADER_HPP
#define HEADER_HPP

#include <vector>
#include <SFML/Graphics.hpp>

struct Vec3d
{
    float x, y, z;
};

struct Triangle
{
    Vec3d p[3];
};

struct Mesh
{
    std::vector<Triangle> triangles;
};

struct Matrix4x4
{
    std::vector<std::vector<float>> m = std::vector(4, std::vector<float>(4));
};

class Engine3d
{
private:
    Mesh meshCube;
    Matrix4x4 projectedMatrix;
    float fTheta = 0;

public:
    Engine3d();
    std::vector<sf::ConvexShape> renderScreen(sf::Vector2u screenSize);

    void multiplyMatrixVector(Vec3d &in, Vec3d &out, Matrix4x4 &matrix)
    {
        out.x = in.x * matrix.m[0][0] + in.y * matrix.m[1][0] + in.z * matrix.m[2][0] + matrix.m[3][0];
        out.y = in.x * matrix.m[0][1] + in.y * matrix.m[1][1] + in.z * matrix.m[2][1] + matrix.m[3][1];
        out.z = in.x * matrix.m[0][2] + in.y * matrix.m[1][2] + in.z * matrix.m[2][2] + matrix.m[3][2];
        float w = in.x * matrix.m[0][3] + in.y * matrix.m[1][3] + in.z * matrix.m[2][3] + matrix.m[3][3];

        if (w != 0.0f)
        {
            out.x /= w;
            out.y /= w;
            out.z /= w;
        }
    }
};

#endif