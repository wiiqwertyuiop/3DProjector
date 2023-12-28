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

std::vector<sf::Vertex> Engine3d::renderScreen(sf::Vector2u screenSize)
{
    std::vector<sf::Vertex> drawObjects;

    Matrix4x4 matRotZ, matRotX;
    fTheta += 1.0f * 0.00003;

    //  Rotation Z
    matRotZ.m = {
        {cosf(fTheta), sinf(fTheta), 0, 0},
        {-sinf(fTheta), cosf(fTheta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    // Rotation X
    matRotX.m = {
        {1, 0, 0, 0},
        {0, cosf(fTheta * 0.5f), sinf(fTheta * 0.5f), 0},
        {0, -sinf(fTheta * 0.5f), cosf(fTheta * 0.5f), 0},
        {0, 0, 0, 1}};

    // Draw triangle
    for (auto triangle : meshCube.triangles)
    {
        Triangle triProjected, triRotatedZ, triRotatedZX;
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
        }

        // Draw object as lines
        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y), sf::Color::White));
        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y), sf::Color::Red));

        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[1].x, triProjected.p[1].y), sf::Color::White));
        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y), sf::Color::Red));

        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[2].x, triProjected.p[2].y), sf::Color::White));
        drawObjects.push_back(sf::Vertex(sf::Vector2f(triProjected.p[0].x, triProjected.p[0].y), sf::Color::Red));
    }

    return drawObjects;
}
