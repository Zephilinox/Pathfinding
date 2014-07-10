//STD
#include <iostream>
#include <vector>

//3RD
#include "SFML/Graphics.hpp"

//SELF
#include "Map.hpp"

void handleEvent(sf::Event& e, sf::RenderWindow& window);
void update(const float dt);
void draw(sf::RenderWindow& window, Map& map);

int main()
{
    Map map;

    sf::RenderWindow window(sf::VideoMode(960, 960), "Pathfinding");

    sf::Clock frameTime;
    sf::Time prevFrameTime = sf::seconds(1.f / 60.f);

    sf::Event event;

    while (window.isOpen())
    {
        window.pollEvent(event);
        handleEvent(event, window);

        update(prevFrameTime.asSeconds());

        draw(window, map);
    }

    return 0;
}

void handleEvent(sf::Event& e, sf::RenderWindow& window)
{
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

void update(const float dt)
{

}

void draw(sf::RenderWindow& window, Map& map)
{
    window.clear(sf::Color(40, 40, 40));
    window.draw(map);
    window.display();
}
