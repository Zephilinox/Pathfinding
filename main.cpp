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
    /*
    Remember to separate the actual tile from the path finding, it should not be necessary to have them in one class.
    The tile holds some kind of entity or terrain, and the nodes hold path finding state
    path finding can have debug drawing turned on/off because it is independent from the tiles, and it can be done easily.
    So if a tile is an empty area or a wall, that's fine, but a node should be the source or target, and a node should hold the F, H and G costs
    */

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
