//STD
#include <iostream>
#include <vector>

//3RD
#include "SFML/Graphics.hpp"

//SELF
#include "Map.hpp"
#include "Constants.hpp"
#include "Pathfinder.hpp"

void handleEvent(sf::Event& e, sf::RenderWindow& window);
void update(const float dt, sf::RenderWindow& window);
void draw(sf::RenderWindow& window);

Map map;
Pathfinder pathfinder(map);

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

        //std::cout << "FPS: " << 1.f / prevFrameTime.asSeconds() << "\n";
        prevFrameTime = frameTime.restart();
    }

    return 0;
}

void handleEvent(sf::Event& e, sf::RenderWindow& window)
{
    map.handleEvent(e, window);
    pathfinder.handleEvent(e, window);

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
    pathfinder.update(dt, window);
}

void draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(40, 40, 40));
    window.draw(map);
    window.display();
}
