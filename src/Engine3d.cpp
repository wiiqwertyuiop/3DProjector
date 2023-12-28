#include "Engine3d.h"
#include <math.h>
#include <iostream>

Engine3d::Engine3d()
{
    meshCube.triangles = {
        // SOUTH
        {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        // EAST
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

        // NORTH
        {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

        // WEST
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

        // TOP
        {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

        // BOTTOM
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
    };

    // Projection matrix
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    float fov = 90.0f;
    float projEquationResult = 1.0f / tanf(fov * 0.5f / 180.0f * M_PI);

    projectedMatrix.m = {
        {projEquationResult, 0, 0, 0},
        {0, projEquationResult, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 0}};
}

std::vector<sf::ConvexShape> Engine3d::renderScreen(sf::Vector2u screenSize)
{
    std::vector<sf::ConvexShape> drawObjects;

    Matrix4x4 matRotZ, matRotX;
    fTheta += 1.0f * 0.00007;

    //  Rotation Z
    matRotZ.m[0][0] = cosf(fTheta);
    matRotZ.m[0][1] = sinf(fTheta);
    matRotZ.m[1][0] = -sinf(fTheta);
    matRotZ.m[1][1] = cosf(fTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;

    // Rotation X
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = cosf(fTheta * 0.5f);
    matRotX.m[1][2] = sinf(fTheta * 0.5f);
    matRotX.m[2][1] = -sinf(fTheta * 0.5f);
    matRotX.m[2][2] = cosf(fTheta * 0.5f);
    matRotX.m[3][3] = 1;

    // Draw triangle
    for (auto triangle : meshCube.triangles)
    {
        Triangle triProjected, triRotatedZ, triRotatedZX;

        sf::ConvexShape drawObj;

        drawObj.setPointCount(3);
        drawObj.setFillColor(sf::Color::Transparent);
        drawObj.setOutlineColor(sf::Color::White);
        drawObj.setOutlineThickness(2.0f);

        // Project 3D -> 2D
        for (int i = 0; i < 3; i++)
        {
            // Rotate in Z-Axis
            multiplyMatrixVector(triangle.p[i], triRotatedZ.p[i], matRotZ);
            // Rotate in X-Axis
            multiplyMatrixVector(triRotatedZ.p[i], triRotatedZX.p[i], matRotX);
            // Translated
            triRotatedZX.p[i].z = triRotatedZX.p[i].z + 3.0f;
            multiplyMatrixVector(triRotatedZX.p[i], triProjected.p[i], projectedMatrix);

            // Scale into view
            triProjected.p[i].x += 1.0f;
            triProjected.p[i].y += 1.0f;

            triProjected.p[i].x *= 0.5f * (float)screenSize.x;
            triProjected.p[i].y *= 0.5f * (float)screenSize.y;
            // Draw object as lines
            drawObj.setPoint(i, sf::Vector2f(triProjected.p[i].x, triProjected.p[i].y));
        }
        drawObjects.push_back(drawObj);
    }

    return drawObjects;
}
