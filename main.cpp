//STD
#include <iostream>
#include <vector>

//3RD
#include "SFML/Graphics.hpp"

//SELF
#include "Map.hpp"
#include "Constants.h"

void handleEvent(sf::Event& e, sf::RenderWindow& window);
void update(const float dt, sf::RenderWindow& window);
void draw(sf::RenderWindow& window);

Map map;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Constant::windowWidth, Constant::windowHeight), "Pathfinding");

    sf::Clock frameTime;
    sf::Time prevFrameTime = sf::seconds(1.f / 60.f);

    sf::Event event;

    while (window.isOpen())
    {
        window.pollEvent(event);
        handleEvent(event, window);

        update(prevFrameTime.asSeconds(), window);

        draw(window);
    }

    return 0;
}

void handleEvent(sf::Event& e, sf::RenderWindow& window)
{
    map.handleEvent(e, window);

    switch (e.type)
    {
        case (sf::Event::Closed):
        {
            window.close();
            break;
        }

        default:
        {
            return;
        }
    }
}

void update(const float dt, sf::RenderWindow& window)
{
    map.update(dt, window);
}

void draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(40, 40, 40));
    window.draw(map);
    window.display();
}
