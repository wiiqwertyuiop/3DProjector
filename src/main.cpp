#include "Engine3d.h"

int main()
{
    Engine3d engine3d;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1200, 1200)), "3D Test");

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
        window.clear();
        for (auto obj : engine3d.renderScreen(window.getSize()))
            window.draw(obj);
        window.display();
    }
    return 0;
}