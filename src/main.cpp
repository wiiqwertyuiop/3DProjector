#include "Engine3d.h"

int main()
{
    Engine3d engine3d;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Hi");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // Draw screen
        std::vector<sf::Vertex> vertices = engine3d.renderScreen(window.getSize());
        window.clear();
        window.draw(&vertices[0], vertices.size(), sf::PrimitiveType::Lines);
        window.display();
    }
    return 0;
}